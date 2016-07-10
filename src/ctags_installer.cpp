#include <iostream>
#include "install_helper.h"
#include "ctags_installer.h"

using std::cout;
using std::endl;

bool CtagsInstaller::check_ctags()
{
    if ( InstallHelper::get_os() == InstallHelper::UNKNOWN )
    {
        InstallHelper::terminate( "To check Ctags installed, " \
               "this OS is invalid" );
    }

    string cmd;
    string result;

    cmd = "which ctags";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

    if ( !result.empty() )
        return true;
    else
        return false;
}

bool CtagsInstaller::install_ctags()
{
    if ( InstallHelper::get_os() == InstallHelper::UNKNOWN )
    {
        InstallHelper::terminate( "To install Ctags, this OS is invalid" );
    }

    if ( check_ctags() )
    {
        cout << "Ctags is already installed ..." << endl;
        cout << "Ctags install Complete ..." << endl;

        return true;
    }

    string cmd;

    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {
        cmd = "sudo apt-get install -y exuberant-ctags";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        return true;
    }
    else if ( InstallHelper::get_os() == InstallHelper::MAC )
    {
        cmd = "brew install ctags";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        return true;
    }

    return false;
}
