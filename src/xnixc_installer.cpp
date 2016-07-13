#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "install_helper.h"
#include "str_util.h"
#include "xnixc_installer.h"
#include "clang_installer.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;

bool XnixcInstaller::set_makefile( const string lang )
{
    string tar_cmd;
    string new_cmd;
    string f_name;
    string temp_f_name;
    string cmd;
    ifstream r_fs;
    ofstream w_fs;
    string read_line;

    if ( lang == "c" )
    {
        tar_cmd = "###clang_cmd";
        new_cmd = ClangInstaller::get_clang_cmd( "c" );
        f_name = string( getenv( "HOME" ) ) + "/.xnixc/resource/" +
            "Makefile.c.conf";
    }
    else if ( lang == "cpp" )
    {
        tar_cmd = "###clang++_cmd";
        new_cmd = ClangInstaller::get_clang_cmd( "cpp" );
        f_name = string( getenv( "HOME" ) ) + "/.xnixc/resource/" +
            "Makefile.cpp.conf";
    }
    else
    {
        InstallHelper::terminate( "set_makefile : Invalid language type : " +
               lang );
    }
    temp_f_name = f_name + ".temp";

    r_fs.open( f_name );
    if ( !r_fs.is_open() )
        InstallHelper::terminate( "Open failed " + f_name );
    w_fs.open( temp_f_name );
    if ( !w_fs.is_open() )
        InstallHelper::terminate( "Open failed " + temp_f_name );

    while ( getline( r_fs, read_line ) )
    {
        if ( read_line.find( tar_cmd ) != string::npos )
            read_line = StrUtil::str_replace( read_line, tar_cmd, new_cmd );

        w_fs << read_line << endl;
    }

    r_fs.close();
    w_fs.close();

    cmd = "mv " + temp_f_name + " " + f_name;
    InstallHelper::xnix_cmd_exec( cmd.c_str() );

    return true;
}

bool XnixcInstaller::install_xnixc()
{
    InstallHelper::examine_os( "To install xnixc, this OS in invalid" );

    const string bash_cmd = "export PATH=$PATH:$HOME/.xnixc";
    string cmd;
    string bash_f;
    ifstream r_fs;
    string read_line;
    bool is_cmd;

    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {
        bash_f = string( getenv( "HOME" ) ) + "/.bashrc";
    }
    else if ( InstallHelper::get_os() == InstallHelper::MAC )
    {
        bash_f = string( getenv( "HOME" ) ) + "/.bash_profile";
    }

    r_fs.open( bash_f.c_str() );

    is_cmd = false;
    while ( getline( r_fs, read_line ) )
    {
        if ( bash_cmd == read_line )
        {
            is_cmd = true;
            break;
        }
    }

    if ( !is_cmd )
    {
        cmd = "echo " + StrUtil::str_replace( bash_cmd, "$", "\\$" ) + " >> " +
            bash_f;
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        cmd = "source " + bash_f;
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        is_cmd = false;
    }

    cmd = "rm -rf ~/.xnixc";
    InstallHelper::xnix_cmd_exec( cmd.c_str() );

    cmd = "mkdir ~/.xnixc";
    InstallHelper::xnix_cmd_exec( cmd.c_str() );

    cmd = "mkdir ~/.xnixc/resource";
    InstallHelper::xnix_cmd_exec( cmd.c_str() );

    cmd = "cp ../resource/xnixc/xnixc ~/.xnixc";
    InstallHelper::xnix_cmd_exec( cmd.c_str() );

    cmd = "chmod 755 ~/.xnixc/xnixc";
    InstallHelper::xnix_cmd_exec( cmd.c_str() );

    cmd = "cp ../resource/xnixc/*.* ~/.xnixc/resource";
    InstallHelper::xnix_cmd_exec( cmd.c_str() );

    set_makefile( "c" );
    set_makefile( "cpp" );

    return true;
}
