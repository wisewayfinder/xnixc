#include <string>
#include <sstream>
#include <vector>
#include "str_util.h"

using std::string;
using std::stringstream;
using std::vector;

vector< string >& StrUtil::str_split( const string &str, char delim, 
        vector< string >& elems )
{
    stringstream ss( str );
    string item;

    while ( std::getline( ss, item, delim ) )
    {
        elems.push_back( item );
    }

    return elems;
}

vector< string > StrUtil::str_split( const string& str, char delim )
{
    vector< string > elems;
    str_split( str, delim, elems );

    return elems;
}

string StrUtil::str_replace( string str, const string& tar, const string& val )
{
    string::size_type offset = 0;

    while ( true )
    {
        offset = str.find(tar, offset);

        if ( string::npos == offset )
            break;

        str.replace( offset, tar.length(), val );
        offset += val.length();
    }

    return str;
}

string StrUtil::remove_lf( string str )
{
    if ( !str.empty() && str[str.length() - 1] == '\n' )
    {
        str.erase( str.length() - 1 );
    }

    return str;
}
