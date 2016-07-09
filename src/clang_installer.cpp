#include <iostream>
#include <string>
#include <vector>
#include "install_helper.h"
#include "clang_installer.h"
#include "str_util.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

bool ClangInstaller::check_clang()
{
    if ( InstallHelper::get_os() == InstallHelper::UNKNOWN )
    {
        InstallHelper::terminate( "To check Clang installed, " \
                "this OS is invalid" );
    }

    string cmd = "which clang";
    string result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

    if ( !result.empty() )
    {
        return true;
    }
    else
    {
        cmd = "echo $PATH";
        result = InstallHelper::xnix_cmd_exec( cmd.c_str() );
        result = StrUtil::remove_lf( result );
        vector< string > pathes;
        pathes = StrUtil::str_split( result, ':' );

        vector< string >::iterator it = pathes.begin();

        while ( it != pathes.end() )
        {
            cmd = "find " + *it + " -name \"clang*\" 2> /dev/null";
            result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

            if ( !result.empty() )
                return true;

            it++;
        }
    }

    return false;
}

bool ClangInstaller::install_clang()
{
    if ( InstallHelper::get_os() == InstallHelper::UNKNOWN )
    {
        InstallHelper::terminate( "To install Clang, this OS is invalid" );

        return false;
    }

    if ( check_clang() )
    {
        cout << "Clang is already installed..." << endl;
        cout << "Install Complete..." << endl;

        return true;
    }

    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {
        string cmd;
        string result;

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
               "python-clang-3.8 lldb-3.8-dev liblldb-3.8-dbg";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        cmd = "sudo ln -s /usr/bin/clang-3.8 /usr/bin/clang";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        cmd = "sudo ln -s /usr/bin/clang++-3.8 /usr/bin/clang++";
        InstallHelper::xnix_cmd_exec( cmd.c_str() );

        return true;
    }

    return false;
}
