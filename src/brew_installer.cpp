#include <iostream>
#include "install_helper.h"
#include "brew_installer.h"

using std::cout;
using std::endl;

bool BrewInstaller::chk_brew()
{
    if ( InstallHelper::get_os() != InstallHelper::MAC )
        InstallHelper::terminate( "chk_brew is only available on OS X" );

    string cmd;
    string result;

    cmd = "which brew";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

    if ( InstallHelper::FAILED == result )
        return false;
    else
        return true;
}

bool BrewInstaller::install_brew()
{
    if ( InstallHelper::get_os() != InstallHelper::MAC )
        InstallHelper::terminate( "install_brew is only available on OS X" );

    if ( chk_brew() )
    {
        cout << "Brew is already installed ..." << endl;
        cout << "Brew install complete" << endl;

        return true;
    }

    string cmd;
    string result;

    cmd = "/usr/bin/ruby -e \"$(curl -fsSL https://raw.githubusercontent.com/" \
           "Homebrew/install/master/install)\"";
    InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

    if ( chk_brew() )
        return true;
    else
        return false;
}
