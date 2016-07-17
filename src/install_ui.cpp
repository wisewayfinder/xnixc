#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "install_helper.h"
#include "clang_installer.h"
#include "brew_installer.h"
#include "mvim_installer.h"
#include "c_make_installer.h"
#include "cscope_installer.h"
#include "ctags_installer.h"
#include "vim_manager.h"
#include "xnixc_installer.h"
#include "ycm_installer.h"
#include "install_ui.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

bool return_false()
{
    return false;
}

bool return_true()
{
    return true;
}

bool InstallUi::init_cmd_list()
{
    cmd_list.clear();

    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {
        cmd_list.push_back( CmdInfo( "clang", ClangInstaller::check_clang,
                    ClangInstaller::install_clang ) );

        if ( ClangInstaller::check_clang() )
        {
            cmd_list.push_back( CmdInfo( "cmake", CMakeInstaller::check_c_make,
                       CMakeInstaller::install_c_make ) );
        }

        cmd_list.push_back( CmdInfo( "ctags", CtagsInstaller::check_ctags,
                   CtagsInstaller::install_ctags ) );

        cmd_list.push_back( CmdInfo( "cscope", CscopeInstaller::check_cscope,
                   CscopeInstaller::install_cscope ) );

        if ( CtagsInstaller::check_ctags() && CscopeInstaller::check_cscope() )
        {
            if ( vim_inst_state )
            {
                cmd_list.push_back( 
                        CmdInfo( 
                            "vim config",
                            return_true,
                            VimManager::vim_configure 
                            ) 
                        );
            }
            else
            {
                cmd_list.push_back( 
                        CmdInfo( 
                            "vim config",
                            return_false,
                            VimManager::vim_configure 
                            ) 
                        );
            }
        }

        if ( ClangInstaller::check_clang() && CMakeInstaller::check_c_make() )
        {
            cmd_list.push_back( CmdInfo( "YouCompleteMe", YcmInstaller::chk_ycm,
                       YcmInstaller::install_ycm ) );
        }

        if ( ClangInstaller::check_clang() && 
                CtagsInstaller::check_ctags() &&
                CscopeInstaller::check_cscope() &&
                YcmInstaller::chk_ycm() )
        {
            if ( xnixc_inst_state )
            {
                cmd_list.push_back( 
                        CmdInfo( 
                            "xnixc( don't forget source bash )",
                            return_true,
                            XnixcInstaller::install_xnixc 
                            ) 
                        );
            }
            else
            {
                cmd_list.push_back( 
                        CmdInfo( 
                            "xnixc",
                            return_false,
                            XnixcInstaller::install_xnixc 
                            ) 
                        );
            }
        }
    }
    else if ( InstallHelper::get_os() == InstallHelper::MAC )
    {
        cmd_list.push_back( CmdInfo( "homebrew", BrewInstaller::chk_brew, 
                    BrewInstaller::install_brew ) );
        cmd_list.push_back( CmdInfo( "MacVim( don't forget source bash )",
                    MvimInstaller::chk_mvim, 
                    MvimInstaller::install_mvim ) );

        if ( BrewInstaller::chk_brew() )
        {
            cmd_list.push_back( CmdInfo( "clang", ClangInstaller::check_clang,
                        ClangInstaller::install_clang ) );
            cmd_list.push_back( CmdInfo( "cmake", CMakeInstaller::check_c_make,
                        CMakeInstaller::install_c_make ) );
            cmd_list.push_back( CmdInfo( "ctags", CtagsInstaller::check_ctags,
                        CtagsInstaller::install_ctags ) );
            cmd_list.push_back( CmdInfo( "cscope", 
                        CscopeInstaller::check_cscope, 
                        CscopeInstaller::install_cscope ) );

            if ( CtagsInstaller::check_ctags() && 
                    CscopeInstaller::check_cscope() && 
                    MvimInstaller::chk_mvim() )
            {
                if ( vim_inst_state )
                {
                    cmd_list.push_back( 
                            CmdInfo( 
                                "vim config",
                                return_true,
                                VimManager::vim_configure 
                                ) 
                            );
                }
                else
                {
                    cmd_list.push_back( 
                            CmdInfo( 
                                "vim config",
                                return_false,
                                VimManager::vim_configure 
                                ) 
                            );
                }
            }

            if ( ClangInstaller::check_clang() &&
                    CMakeInstaller::check_c_make() &&
                    MvimInstaller::chk_mvim() )
            {
                cmd_list.push_back( CmdInfo( "YouCompleteMe",
                            YcmInstaller::chk_ycm,
                            YcmInstaller::install_ycm ) );
            }

            if ( ClangInstaller::check_clang() && 
                    CtagsInstaller::check_ctags() &&
                    CscopeInstaller::check_cscope() &&
                    MvimInstaller::chk_mvim() && YcmInstaller::chk_ycm() )
            {
                if ( xnixc_inst_state )
                {
                    cmd_list.push_back( 
                            CmdInfo( 
                                "xnixc( don't forget source bash )",
                                return_true, 
                                XnixcInstaller::install_xnixc 
                                ) 
                            );
                }
                else
                {
                    cmd_list.push_back( 
                            CmdInfo( 
                                "xnixc",
                                return_false, 
                                XnixcInstaller::install_xnixc 
                                ) 
                            );
                }
            }
        }
    }
    else
        return false;

    return true;
}

bool InstallUi::draw_cmds()
{
    string install_state;
    size_t idx;

    init_cmd_list();

    cout << endl << "********    xnixc Installer    ********" << endl << endl;

    cout << "[  0 ] ";
    cout.width(12);
    cout << std::left << "All-in-one install" << endl;

    for ( idx = 0; idx < cmd_list.size(); idx++ )
    {
        install_state = (*cmd_list[idx].check_func)() ? "installed" :
            "not installed";

        cout << "[ ";
        cout.width(2);
        cout << std::right << idx + 1 << " ] ";
        cout.width(48);
        cout << std::left << cmd_list[idx].cmd_name;
        cout << "[ " << install_state << " ]" << endl;
    }

    return true;
}

bool InstallUi::install_cmd( int cmd_num )
{
    init_cmd_list();

    if( cmd_num == 0 )
    {
        if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
        {
            ClangInstaller::install_clang();
            CMakeInstaller::install_c_make();
            CtagsInstaller::install_ctags();
            CscopeInstaller::install_cscope();
            VimManager::vim_configure();
            YcmInstaller::install_ycm();
            XnixcInstaller::install_xnixc();

            vim_inst_state = true;
            xnixc_inst_state = true;
        }
        else if ( InstallHelper::get_os() == InstallHelper::MAC )
        {
            BrewInstaller::install_brew();
            MvimInstaller::install_mvim();
            ClangInstaller::install_clang();
            CMakeInstaller::install_c_make();
            CtagsInstaller::install_ctags();
            CscopeInstaller::install_cscope();
            VimManager::vim_configure();
            YcmInstaller::install_ycm();
            XnixcInstaller::install_xnixc();

            vim_inst_state = true;
            xnixc_inst_state = true;
        }

        return true;
    }
    else if ( cmd_num > (int)cmd_list.size() || cmd_num < 0 )
    {
        cout << "invalid command number input" << endl;
        return false;
    }
    else
    {
        if ( cmd_list[ cmd_num - 1 ].install_func == VimManager::vim_configure )
            vim_inst_state = true;

        if ( cmd_list[ cmd_num - 1 ].install_func == 
                XnixcInstaller::install_xnixc )
            xnixc_inst_state = true;
        
        return (*cmd_list[cmd_num - 1].install_func)();
    }
}

InstallUi::InstallUi() : vim_inst_state( false ), xnixc_inst_state( false )
{
    init_cmd_list();
}

bool InstallUi::draw_ui()
{
    int key_stk;

    while ( true )
    {
        draw_cmds();

        cout << endl << "[ -1 ] ";
        cout.width(12);
        cout << std::left << "exit" << endl << endl;
        cout << "select number to install >> ";
        cin >> key_stk;
        cout << endl;

        if ( key_stk == -1 )
        {
            cout << endl << "Exit ..." << endl;
            cout << endl << "Exit complete" << endl << endl;
            break;
        }

        install_cmd( key_stk );
    }

    return true;
}
