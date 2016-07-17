#include <iostream>
#include "install_helper.h"
#include "brew_installer.h"
#include "ctags_installer.h"

using std::cout;
using std::endl;

bool CtagsInstaller::check_ctags()
{
    InstallHelper::examine_os( "To check Ctags installed, this OS is invalid" );

    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {
        string cmd;
        string result;

        cmd = "which ctags";
        result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

        if ( result != InstallHelper::FAILED )
            return true;
        else
            return false;
    }
    else if ( InstallHelper::get_os() == InstallHelper::MAC )
    {
        if ( BrewInstaller::chk_pack( "ctags" ) )
            return true;
        else
            return false;
    }
    else
        return false;
}

bool CtagsInstaller::install_ctags()
{
    InstallHelper::examine_os( "To install Ctags, this OS is invalid" );

    if ( check_ctags() )
    {
        cout << "Ctags is already installed ..." << endl;
        cout << "Ctags install complete" << endl;

        return true;
    }

    string cmd;

    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {
        cmd = "sudo apt-get install -y exuberant-ctags";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );
    }
    else if ( InstallHelper::get_os() == InstallHelper::MAC )
    {
        if ( !BrewInstaller::chk_brew() )
        {
            cout << "Before Ctags install, need HomeBrew ...";
            cout << "Ctags install failed" << endl;

            return false;
        }

        cmd = "brew install ctags";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );
    }

    if ( check_ctags() )
        return true;
    else
        return false;
}
