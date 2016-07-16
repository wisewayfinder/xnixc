#include <iostream>
#include <string>
#include <vector>
#include "install_helper.h"
#include "clang_installer.h"
#include "str_util.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

bool ClangInstaller::find_clang_cmd( const string& str, const string& lang )
{
    string cmd;
    string cmp_cmd;
    size_t pos;

    cmd = *(StrUtil::str_split( StrUtil::remove_lf( str ), '/' ).end() - 1);

    if ( lang == "c" )
    {
        cmp_cmd = "clang-";
    }
    else if ( lang == "cpp" )
    {
        cmp_cmd = "clang++-";
    }
    else
        InstallHelper::terminate( "find_clang_cmd: invalid language input" );

    if ( cmd.length() <= cmp_cmd.length() )
        return false;

    pos = cmd.find( cmp_cmd );

    if ( pos == string::npos )
        return false;

    pos += cmp_cmd.length();

    if ( cmd[pos] < 48 || cmd[pos] > 57 )
        return false;

    bool searched_comma = false;
    for ( pos += 1; pos < cmd.length(); pos++ )
    {
        if ( cmd[pos] == '.')
        {
            if ( !searched_comma && pos != cmd.length() - 1 )
            {
                searched_comma = true;
                continue;
            }
            else
            {
                return false;
            }
        }

        if ( cmd[pos] < 48 || cmd[pos] > 57 )
            return false;
    }

    return true;
}

string ClangInstaller::get_clang_path( const string& lang )
{
    string cmd;
    string result;

    if ( lang == "c" )
        cmd = "which clang";
    else if ( lang == "cpp" )
        cmd = "which clang++";
    else
        InstallHelper::terminate( "To get clang path, invalid language type" );

    result = StrUtil::remove_lf( InstallHelper::xnix_cmd_exec( cmd.c_str() ) );
    if ( result != InstallHelper::FAILED )
        return result;

    vector< string > pathes;
    vector< string >::iterator path_iter;

    cmd = "echo $PATH";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str() );
    result = StrUtil::remove_lf( result );
    pathes = StrUtil::str_split( result, ':' );

    for ( path_iter = pathes.begin(); path_iter != pathes.end(); path_iter++ )
    {
        cmd = "find " + *path_iter + " -name \"clang*\" 2> /dev/null";
        result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

        if ( !result.empty() )
        {
            vector< string > searched_cmds = StrUtil::str_split( result, '\n' );
            vector< string >::iterator cmd_it;

            for ( cmd_it = searched_cmds.begin(); cmd_it != searched_cmds.end();
                    cmd_it++ )
            {
                if ( find_clang_cmd( *cmd_it, lang ) )
                    return *cmd_it;
            }
        }
    }

    return InstallHelper::FAILED;
}

string ClangInstaller::get_clang_cmd( const string& lang )
{
    string path = get_clang_path( lang );
    string cmd = *(StrUtil::str_split( path, '/' ).end() - 1);

    return cmd;
}

bool ClangInstaller::check_clang()
{
    InstallHelper::examine_os( "To check Clang installed, this OS is invalid");

    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {
        if ( get_clang_path( "c" ) == InstallHelper::FAILED || 
                get_clang_path( "cpp" ) == InstallHelper::FAILED )
            return false;
        else
            return true;
    }
    else if ( InstallHelper::get_os() == InstallHelper::MAC )
    {
        string cmd = "find /Library/Developer/CommandLineTools 2> /dev/null";
        string result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

        if ( InstallHelper::FAILED == result )
            return false;
        else
            return true;
    }
    else
        return false;
}

bool ClangInstaller::install_clang()
{
    InstallHelper::examine_os( "To install Clang, this OS is invalid" );

    string cmd;
    string result;

    if ( check_clang() )
    {
        cout << "Clang is already installed ..." << endl;
        cout << "Clang install complete" << endl;

        if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
        {
            cmd = "which clang";
            result = InstallHelper::xnix_cmd_exec( cmd.c_str() );
            if ( InstallHelper::FAILED == result )
            {
                cmd = "sudo ln -s " + get_clang_path( "c" ) + " /usr/bin/clang";
                InstallHelper::xnix_cmd_exec( cmd.c_str(), false);
            }

            cmd = "which clang++";
            result = InstallHelper::xnix_cmd_exec( cmd.c_str() );
            if ( InstallHelper::FAILED == result )
            {
                cmd = "sudo ln -s " + get_clang_path( "cpp" ) + 
                    " /usr/bin/clang++";
                InstallHelper::xnix_cmd_exec( cmd.c_str(), false );
            }
        }

        return true;
    }

    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {
        cmd = "sudo apt-add-repository --remove -y ppa:ubuntu-toolchain-r/test";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

        cmd = "sudo apt-add-repository -y ppa:ubuntu-toolchain-r/test";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

        cmd = "sudo apt-add-repository --remove -y \"deb http://llvm.org/apt/" \
               "trusty/ llvm-toolchain-trusty-3.8 main\"";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

        cmd = "sudo apt-add-repository -y \"deb http://llvm.org/apt/trusty/ " \
               "llvm-toolchain-trusty-3.8 main\"";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

        cmd = "wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key|" \
               "sudo apt-key add -";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

        cmd = "sudo apt-get update";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

        cmd = "sudo apt-get install -y clang-3.8 clang-3.8-doc " \
               "libclang-common-3.8-dev libclang-3.8-dev libclang1-3.8 " \
               "libclang1-3.8-dbg libllvm-3.8-ocaml-dev libllvm3.8 " \
               "libllvm3.8-dbg lldb-3.8 llvm-3.8 llvm-3.8-dev llvm-3.8-doc " \
               "llvm-3.8-examples llvm-3.8-runtime clang-format-3.8 " \
               "python-clang-3.8 lldb-3.8-dev liblldb-3.8-dbg libc++-dev " \
               "libc++abi-dev";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

        cmd = "sudo ln -s /usr/bin/clang-3.8 /usr/bin/clang";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

        cmd = "sudo ln -s /usr/bin/clang++-3.8 /usr/bin/clang++";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );
    }
    else if ( InstallHelper::get_os() == InstallHelper::MAC )
    {
        cmd = "xcode-select --install";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );
    }

    if ( check_clang() )
        return true;
    else
        return false;
}
