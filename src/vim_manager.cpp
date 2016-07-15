#include <iostream>
#include "install_helper.h"
#include "cscope_installer.h"
#include "ctags_installer.h"
#include "str_util.h"
#include "vim_manager.h"

bool VimManager::check_vundle()
{
    InstallHelper::examine_os( "To check Vundle installed, this OS is " \
            "invalid" );

    string cmd; 
    string result;

    cmd = "find ~/.vim/bundle/Vundle.vim 2> /dev/null";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

    if ( result != InstallHelper::FAILED )
        return true;
    else
        return false;
}

bool VimManager::vimrc_configure()
{
    InstallHelper::examine_os( "To configure vimrc, this OS is invalid" );

    string cmd;
    string result;

    if ( !CscopeInstaller::check_cscope() )
        InstallHelper::terminate( "Cscope isn't installed in this system" );

    if ( !CtagsInstaller::check_ctags() )
        InstallHelper::terminate( "Ctags isn't installed in this system" );

    cmd = "mkdir ~/.vimbackup";
    InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

    cmd = "cp ../resource/vimrc ~/.vimrc";
    result = InstallHelper::xnix_cmd_exec( cmd.c_str(), false );
    
    if ( result == InstallHelper::FAILED )
        InstallHelper::terminate( "Can't copy vimrc file" );

    cmd = "which cscope";
    result = StrUtil::remove_lf( InstallHelper::xnix_cmd_exec( cmd.c_str() ) );

    cmd = "sed -i -e \"s/##cscope_path/" + 
        StrUtil::str_replace( result, "/", "\\/" ) + "/g\" ~/.vimrc";
                    std::cout << cmd << std::endl;
    InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

    cmd = "which ctags";
    result = StrUtil::remove_lf( InstallHelper::xnix_cmd_exec( cmd.c_str() ) );

    cmd = "sed -i -e \"s/##ctags_path/\\\"" + 
        StrUtil::str_replace( result, "/", "\\/" ) + "\\\"/g\" ~/.vimrc";
    InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

    return true;
}

bool VimManager::vundle_install()
{
    InstallHelper::examine_os( "To Vundle install, this OS is invalid" );

    if ( check_vundle() )
        return true;
    else
    {
        string cmd;

        cmd = "git clone https://github.com/VundleVim/Vundle.vim.git " \
               "~/.vim/bundle/Vundle.vim";
        InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

        return true;
    }

    return false;
}

bool VimManager::plugin_install()
{
    InstallHelper::examine_os( "To plugin install with Vundle, this OS is " \
            "invalid" );

    if ( !check_vundle() )
        InstallHelper::terminate( "Vundle is not installed" );

    string cmd;
    string result;
    
    cmd = "echo | vim +PluginInstall +qall";
    InstallHelper::xnix_cmd_exec( cmd.c_str(), false );

    return true;
}

bool VimManager::vim_configure()
{
    vimrc_configure();
    vundle_install();
    plugin_install();

    return true;
}
