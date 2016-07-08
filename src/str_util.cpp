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
