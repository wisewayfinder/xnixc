#include <iostream>
#include "install_helper.h"
#include "brew_installer.h"
#include "cscope_installer.h"

using std::cout;
using std::endl;

bool CscopeInstaller::check_cscope()
{
    InstallHelper::examine_os( "To check Cscope installed, this OS is " \
            "invalid" );

    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {
        string cmd;
        string result;

        cmd = "which cscope";
        result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

        if ( result != InstallHelper::FAILED )
            return true;
        else
            return false;
    }
    else if ( InstallHelper::get_os() == InstallHelper::MAC )
    {
        if ( BrewInstaller::chk_pack( "cscope" ) )
            return true;
        else
            return false;
    }
    else
        return false;
}

bool CscopeInstaller::install_cscope()
{
    InstallHelper::examine_os( "To install Cscope, this OS in invalid" );

    if ( check_cscope() )
    {
        cout << "Cscope is already installed ..." << endl;
        cout << "Cscope install complete" << endl;

        return true;
    }

    string cmd;

    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {
        cmd = "sudo apt-get install -y cscope";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

        return true;
    }
    else if ( InstallHelper::get_os() == InstallHelper::MAC )
    {
        if ( !BrewInstaller::chk_brew() )
        {
            cout << "Before cscope install, need HomeBrew ...";
            cout << "cscope install failed" << endl;

            return false;
        }
        cmd = "brew install cscope";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

        return true;
    }

    if ( check_cscope() )
        return true;
    else
        return false;
}
