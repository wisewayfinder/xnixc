#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "install_helper.h"
#include "str_util.h"
#include "clang_installer.h"
#include "ycm_installer.h"

using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::vector;
using std::ofstream;
using std::ifstream;

const string YcmInstaller::extra_conf_path = string( getenv( "HOME" ) ) + 
    "/.vim/ycm_extra_conf_set/";

bool YcmInstaller::chk_ycm()
{
    const string path = "~/.vim/bundle/YouCompleteMe/third_party/ycmd/";
    string cmd;
    string result;
    vector< string > files;
    vector< string >::iterator it;

    files.push_back( "clang_archives/" );
    files.push_back( "PYTHON_USED_DURING_BUILDING" );
    files.push_back( "ycm_core.so" );

    for ( it = files.begin(); it != files.end(); it++ )
    {
        cmd = "find " + path + *it + " 2> /dev/null";
        result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

        if ( InstallHelper::FAILED == result )
            return false;
    }

    return true;
}

vector< string > YcmInstaller::get_sys_header_path( string language )
{
    string cmd;
    string result;
    const string c_info_file = extra_conf_path + "c_sys_header_info.txt";
    const string cpp_info_file = extra_conf_path + "cpp_sys_header_info.txt";
    string info_file;
    ifstream r_fs;
    const string start_delim = "#include <...> search starts here:";
    const string end_delim = "End of search list.";
    string read_line;
    bool valid_line;
    vector< string > headers;

    if ( language == "c" )
    {
        cmd = "echo | " + ClangInstaller::get_clang_cmd( "c" ) +
            " -std=c99 -v -E -x c - 2> " + c_info_file;
        info_file = c_info_file;
    }
    else if ( language == "cpp" )
    {
        cmd = "echo | " + ClangInstaller::get_clang_cmd( "cpp" ) +
            " -std=c++11 -stdlib=libc++ -v -E -x c++ - 2>" + cpp_info_file;
        info_file = cpp_info_file;
    }
    else
    {
        InstallHelper::terminate( "get_sys_header_path: " \
                "This language is not supported" );
    }

    result = InstallHelper::xnix_cmd_exec( cmd.c_str() );
    if ( result == InstallHelper::FAILED )
        InstallHelper::terminate( "Can't create " + info_file );

    r_fs.open( info_file.c_str() );
    valid_line = false;

    if ( !r_fs.is_open() )
        InstallHelper::terminate( "Can't open " + info_file );

    while ( getline( r_fs, read_line ) )
    {
        if ( !valid_line && start_delim == read_line )
        {
            valid_line = true;
            continue;
        }
        if ( valid_line && end_delim == read_line )
            break;

        if ( valid_line )
        {
            read_line.erase(0, 1);
            headers.push_back( read_line );
        }
    }

    r_fs.close();

    cmd = "rm " + info_file;
    InstallHelper::xnix_cmd_exec( cmd.c_str() );

    return headers;
}

bool YcmInstaller::set_extra_conf( string language )
{
    string cmd;
    const string r_fname = extra_conf_path + "ycm_extra_conf." + language +
        ".py";
    const string w_fname = r_fname + ".bak";
    ifstream r_fs;
    ofstream w_fs;
    const string start_delim = "###system_include_pos_start###";
    vector< string > sys_headers;
    string read_line;
    bool coping;

    r_fs.open( r_fname.c_str() );
    if ( !r_fs.is_open() )
        InstallHelper::terminate( "Open fail " + r_fname );
    w_fs.open( w_fname.c_str() );
    if ( !w_fs.is_open() )
        InstallHelper::terminate( "Create fail" + w_fname );

    sys_headers = get_sys_header_path( language );
    coping = false;

    while ( getline( r_fs, read_line ) )
    {
        if ( coping )
        {
            vector< string >::iterator it;

            for ( it = sys_headers.begin(); it != sys_headers.end(); it++ )
            {
                w_fs << "'-isystem'," << endl;
                w_fs << "'" << *it << "'," << endl;
            }

            coping = false;
        }

        if ( !coping && start_delim == read_line )
            coping = true;

        w_fs << read_line << endl;
    }

    r_fs.close();
    w_fs.close();

    cmd = "mv " + w_fname + " " + r_fname;
    InstallHelper::xnix_cmd_exec( cmd.c_str() );

    return true;
}

bool YcmInstaller::ycm_extra_conf_configure()
{
    InstallHelper::examine_os( "To set ycm_extra_conf, this OS is invalid" );

    string cmd;
    string result;

    cmd = "cp -rf ../resource/ycm_extra_conf_set/ ~/.vim/ycm_extra_conf_set/";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

    if ( result == InstallHelper::FAILED )
        InstallHelper::terminate( "Can't copy ycm_extra_conf_set directory" );
    else
    {
        set_extra_conf( "c" );
        set_extra_conf( "cpp" );

        return true;
    }

    return false;
}

bool YcmInstaller::restore_ycm()
{
    InstallHelper::examine_os( "To restore Ycm, this OS is invalid" );

    string cmd;
    string result;

    if ( !ycm_extra_conf_configure() )
        InstallHelper::terminate( "ycm_extra_conf_configure failed" );

    cmd = "which python";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str() );
    if ( result == InstallHelper::FAILED )
    {
        InstallHelper::terminate( "Since python is not installed in this " \
                "system, can't proceed install(restore) Ycm" );
    }

    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {
        cmd = "sudo apt-get install -y build-essential python-dev python3-dev";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );
    }

    cmd = "cd ~/.vim/bundle/YouCompleteMe && ./install.py --clang-completer";
    InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

    return true;
}

bool YcmInstaller::install_ycm()
{
    InstallHelper::examine_os( "To install Ycm, this OS is invalid" );

    bool result;

    if ( chk_ycm() )
    {
        cout << "Ycm is already installed ..." << endl;
        cout << "Ycm install complete" << endl;

        return true;
    }

    result = restore_ycm();

    return result;
}

