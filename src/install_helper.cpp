#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include "install_helper.h"

using std::cout;
using std::endl;
using std::string;
using std::exception;
using std::runtime_error;

const string InstallHelper::UBUNTU = "ubuntu";
const string InstallHelper::MAC = "mac";
const string InstallHelper::UNKNOWN = "unknown";

const string InstallHelper::xnix_cmd_exec( const char* cmd )
{
    const int BUFF_SIZE = 256;

    char buffer[BUFF_SIZE];
    string result = "";
    FILE* pipe = popen( cmd, "r" );

    if ( !pipe )
        throw runtime_error( "popen() failed" );

    try
    {
        while ( !feof( pipe ) )
        {
            if ( fgets( buffer, BUFF_SIZE, pipe ) != NULL )
                result += buffer;
        }
    }
    catch ( runtime_error rte )
    {
        cout << "xnix command |" << cmd << "| failed during runtime..." << endl;
        cout << rte.what() << endl;
        cout << "Termiated...(-1)" << endl;

        pclose( pipe );

        exit( -1 );
    }
    catch ( exception exc )
    {
        cout << "xnix command |" << cmd << "| is failed..." << endl;
        cout << exc.what() << endl;
        cout << "Termiated...(-1)" << endl;

        pclose( pipe );

        exit( -1 );
    }

    pclose( pipe );

    return result;
}

const string InstallHelper::get_os()
{
    try
    {
#ifdef __linux__
        string uname_result = xnix_cmd_exec( "uname -a" );
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
        exit( -1 );
    }
}
