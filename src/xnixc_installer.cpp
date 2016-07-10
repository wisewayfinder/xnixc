#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "install_helper.h"
#include "str_util.h"
#include "xnixc_installer.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;

bool XnixcInstaller::install_xnixc()
{
    InstallHelper::examine_os( "To install xnixc, this OS in invalid" );

    const string bash_cmd = "export PATH=$PATH:$HOME/.xnixc";
    string cmd;
    string result;
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

    cmd = "cp ../resource/xnixc/*.* ~/.xnixc/resource";
    InstallHelper::xnix_cmd_exec( cmd.c_str() );

    return true;
}
