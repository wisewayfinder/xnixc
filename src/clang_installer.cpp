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
        InstallHelper::terminate( "For install Clang, this OS is invalid" );

    string cmd = "which clangs";
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
            cmd = "find " + *it + " -name \"clang*\"";
            result = InstallHelper::xnix_cmd_exec( cmd.c_str() );

            it++;
        }
    }

    // which 로 clang 이 존재하면 그 경로 리턴,
    // 아니라면 os에 알맞는 경로 리턴
    if ( InstallHelper::get_os() == InstallHelper::UBUNTU )
    {

    }
    else if ( InstallHelper::get_os() == InstallHelper::MAC )
    {

    }
    else if ( InstallHelper::get_os() == InstallHelper::UNKNOWN )
    {
        
    }
    else
    {
        
    }
    return true;
}

bool ClangInstaller::install_clang()
{
    return check_clang();
}
