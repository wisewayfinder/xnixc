#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "install_helper.h"
#include "clang_installer.h"
#include "str_util.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::regex;
using std::regex_search;

string ClangInstaller::get_clang_path( string lang )
{
    string cmd;
    string result;
    string cmd_name;
    regex cmd_regex;

    if ( lang == "c" )
    {
        cmd_name = "clang";
        cmd_regex = regex( "(clang$|clang-\\d+\\.\\d+$)" );
    }
    else if ( lang == "cpp" )
    {
        cmd_name = "clang++";
        cmd_regex = regex( "(clang\\+\\+$|clang\\+\\+-\\d+\\.\\d+$)" );
    }
    else
        InstallHelper::terminate( "To get clang path, invalid language type" );

    cmd = "which " + cmd_name;
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
                if ( regex_search( *cmd_it, cmd_regex ) )
                    return *cmd_it;
            }
        }
    }

    return InstallHelper::FAILED;
}

string ClangInstaller::get_clang_cmd( string lang )
{
    string path = get_clang_path( lang );
    string cmd = *(StrUtil::str_split( path, '/' ).end() - 1);

    return cmd;
}

bool ClangInstaller::check_clang()
{
    InstallHelper::examine_os( "To check Clang installed, this OS is invalid");

    if ( get_clang_path( "c" ) == InstallHelper::FAILED || 
            get_clang_path( "cpp" ) == InstallHelper::FAILED )
        return false;
    else
        return true;
}

bool ClangInstaller::install_clang()
{
    InstallHelper::examine_os( "To install Clang, this OS is invalid" );

    if ( check_clang() )
    {
        cout << "Clang is already installed ..." << endl;
        cout << "Clang install complete" << endl;

        return true;
    }

    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {
        string cmd;

        cmd = "sudo apt-add-repository --remove -y ppa:ubuntu-toolchain-r/test";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        cmd = "sudo apt-add-repository -y ppa:ubuntu-toolchain-r/test";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        cmd = "sudo apt-add-repository --remove -y \"deb http://llvm.org/apt/" \
               "trusty/ llvm-toolchain-trusty-3.8 main\"";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        cmd = "sudo apt-add-repository -y \"deb http://llvm.org/apt/trusty/ " \
               "llvm-toolchain-trusty-3.8 main\"";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        cmd = "wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key|" \
               "sudo apt-key add -";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        cmd = "sudo apt-get update";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        cmd = "sudo apt-get install -y clang-3.8 clang-3.8-doc " \
               "libclang-common-3.8-dev libclang-3.8-dev libclang1-3.8 " \
               "libclang1-3.8-dbg libllvm-3.8-ocaml-dev libllvm3.8 " \
               "libllvm3.8-dbg lldb-3.8 llvm-3.8 llvm-3.8-dev llvm-3.8-doc " \
               "llvm-3.8-examples llvm-3.8-runtime clang-format-3.8 " \
               "python-clang-3.8 lldb-3.8-dev liblldb-3.8-dbg libc++-dev " \
               "libc++abi-dev";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        cmd = "sudo ln -s /usr/bin/clang-3.8 /usr/bin/clang";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        cmd = "sudo ln -s /usr/bin/clang++-3.8 /usr/bin/clang++";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        return true;
    }

    return false;
}
