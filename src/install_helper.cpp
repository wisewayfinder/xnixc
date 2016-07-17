#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include "str_util.h"
#include "install_helper.h"

using std::cout;
using std::endl;
using std::string;
using std::exception;
using std::runtime_error;

InstallHelper::InstallHelper() {}

const string InstallHelper::UBUNTU = "ubuntu";
const string InstallHelper::MAC = "mac";
const string InstallHelper::UNKNOWN = "unknown";

const string InstallHelper::FAILED = "failed";

const string InstallHelper::get_home()
{
    return string( getenv("HOME") );
}

const string InstallHelper::xnix_cmd_exec( const char* cmd,
        bool silent /* = true */ )
{
    const int BUFF_SIZE = 256;

    char buffer[BUFF_SIZE];
    string result = "";
    FILE* pipe = popen( cmd, "r" );

    if ( !pipe )
        throw runtime_error( "popen() failed" );

    try
    {
        if ( !silent )
        {
            cout << "******** EXECUTE : " << cmd << " ..." << " ********" <<
                endl;
        }

        while ( !feof( pipe ) )
        {
            if ( fgets( buffer, BUFF_SIZE, pipe ) != NULL )
            {
                if ( !silent )
                    cout << buffer;
                result += buffer;
            }

        }

        int status = pclose( pipe );
        status = WEXITSTATUS( status );

        if ( !silent )
            cout << status << endl;

        if ( status != 0 )
            throw runtime_error( string(cmd) );
    }
    catch ( runtime_error rte )
    {
        if ( !silent )
        {
            cout << "xnix command '" << cmd << "' failed during runtime ..." 
                << endl;
            cout << rte.what() << endl;
        }

        return FAILED;
    }
    catch ( exception exc )
    {
        cout << "xnix command '" << cmd << "' is failed ..." << endl;
        cout << exc.what() << endl;

        return FAILED;
    }

    return result;
}

const string InstallHelper::get_os()
{
    try
    {
#ifdef __linux__
        string uname_result = xnix_cmd_exec( "uname -v" );
        uname_result = StrUtil::str_lower( uname_result );

        if ( uname_result.find( UBUNTU ) == string::npos )
            throw runtime_error( "This linux type '" + uname_result + "'" + 
                    " isn't ubuntu, unavailable" );
        else
            return UBUNTU;
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        return MAC;
    #else
        throw runtime_error( "This apple platform is unkown, unavailable" );
    #endif
#endif
    }
    catch ( exception& exc )
    {
        cout << exc.what() << endl;

        return UNKNOWN;
    }
}

void InstallHelper::examine_os( string err_msg )
{
    if ( get_os() == UNKNOWN )
    {
        terminate( err_msg );
    }
}

bool InstallHelper::terminate( string reason /* = string("") */ )
{
    if ( !reason.empty() )
    {
        cout << "InstallHelper terminate install ... !!!" << endl;
        cout << "    reason : " << reason << endl;
    }

    cout << "Something is invalid for install" << endl;
    cout << "Terminate install ..." << endl;
    cout << "exit(-1)" << endl;

    exit(-1);
}
