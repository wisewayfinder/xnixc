#include <iostream>
#include <fstream>
#include "install_helper.h"
#include "str_util.h"
#include "brew_installer.h"
#include "mvim_installer.h"

using std::cout;
using std::endl;
using std::ifstream;

bool MvimInstaller::set_bash()
{
    string cmd;
    string result;
    ifstream r_fs;
    bool alias_vi = false;
    bool alias_vim = false;
    bool set_visual = false;
    bool set_editor = false;
    const string f_name = string( getenv("HOME") ) + "/.bash_profile";
    const string vi_cmd = "alias vi=\"mvim -v\"";
    const string vim_cmd = "alias vim=\"mvim -v\"";
    const string visual_cmd = "export VISUAL=\"mvim -v\"";
    const string editor_cmd = "export EDITOR=\"$VISUAL\"";
    string read_line;

    r_fs.open( f_name.c_str() );
    while ( !r_fs.is_open() )
    {
        cmd = "find " + f_name + " 2> /dev/null";
        result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

        if ( InstallHelper::FAILED == result )
        {
            cmd = "touch " + f_name;
            InstallHelper::xnix_cmd_exec( cmd.c_str() );

            r_fs.open( f_name.c_str() );
        }
        else
            InstallHelper::terminate( "set_bash: Open failed " + f_name );
    }

    while ( getline( r_fs, read_line ) )
    {
        if ( read_line.find( vi_cmd ) != string::npos )
            alias_vi = true;

        if ( read_line.find( vim_cmd ) != string::npos )
            alias_vim = true;

        if ( read_line.find( visual_cmd ) != string::npos )
            set_visual = true;

        if ( read_line.find( editor_cmd ) != string::npos )
            set_editor = true;
    }

    if ( !alias_vi )
    {
        cmd = "echo " + StrUtil::str_replace( vi_cmd, "\"", "\\\"" ) + " >> " +
            f_name;
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );
    }

    if ( !alias_vim )
    {
        cmd = "echo " + StrUtil::str_replace( vim_cmd, "\"", "\\\"" ) + " >> " +
            f_name;
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );
    }

    if ( !set_visual )
    {
        cmd = "echo " + StrUtil::str_replace( visual_cmd, "\"", "\\\"" ) + 
            " >> " + f_name;
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

        cmd = StrUtil::str_replace( editor_cmd, "\"", "\\\"" );
        cmd = StrUtil::str_replace( cmd, "$", "\\$" );
        cmd = "echo " + cmd + " >> " + f_name;
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );
    }

    if ( set_visual && !set_editor )
    {
        cmd = StrUtil::str_replace( editor_cmd, "\"", "\\\"" );
        cmd = StrUtil::str_replace( cmd, "$", "\\$" );
        cmd = "echo " + cmd + " >> " + f_name;
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );
    }

    r_fs.close();

    return true;
}

bool MvimInstaller::chk_mvim()
{
    if ( InstallHelper::get_os() != InstallHelper::MAC )
        InstallHelper::terminate( "chk_mvim is only available on OS X" );

    string cmd;
    string result;

    cmd = "which mvim";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

    if ( InstallHelper::FAILED == result )
        return false;
    else
    {
        set_bash();

        return true;
    }
}

bool MvimInstaller::install_mvim()
{
    if ( InstallHelper::get_os() != InstallHelper::MAC )
        InstallHelper::terminate( "install_mvim is only available on OS X" );

    if ( chk_mvim() )
    {
        cout << "Mvim is already installed ..." << endl;
        cout << "Mvim install complete" << endl;

        return true;
    }

    string cmd;
    string result;
    string disk_name;

    cmd = "cd ~/Downloads && curl -L -O https://github.com/macvim-dev/macvim/" \
           "releases/download/snapshot-104/MacVim.dmg";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

    if ( InstallHelper::FAILED == result )
        InstallHelper::terminate( "install_mvim: download mvim failed" );

    cmd = "hdiutil attach " + InstallHelper::get_home() + 
        "/Downloads/MacVim.dmg";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

    if ( InstallHelper::FAILED == result )
        InstallHelper::terminate( "install_mvim: open mvim dmg failed" );

    disk_name = *(StrUtil::str_split( result, '\n' ).end() - 1);
    disk_name = *(StrUtil::str_split( disk_name, ' ' ).begin());

    cmd = "cd /Volumes/MacVim/ && cp -rf MacVim.app Applications";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

    if ( InstallHelper::FAILED == result )
        InstallHelper::terminate( "install_mvim: copy MacVim failed" );

    cmd = "find /usr/local/bin";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

    if ( InstallHelper::FAILED == result )
    {
        cmd = "sudo mkdir /usr/local/bin";
        result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

        if ( InstallHelper::FAILED == result )
        {
            InstallHelper::terminate( "install_mvim: create /usr/local/bin " \
                    "failed" );
        }
    }

    cmd = "cd /Volumes/MacVim/ && sudo cp mvim /usr/local/bin";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

    if ( InstallHelper::FAILED == result )
        InstallHelper::terminate( "install_mvim: cp mvim failed" );

    set_bash();

    cmd = "hdiutil detach " + disk_name;
    InstallHelper::xnix_cmd_exec( cmd.c_str() );

    cmd = "rm ~/Downloads/MacVim.dmg";
    InstallHelper::xnix_cmd_exec( cmd.c_str() );

    if ( chk_mvim() )
        return true;
    else
        return false;
}
