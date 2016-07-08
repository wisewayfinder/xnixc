#include <string>
#include <sstream>
#include <vector>

using std::string;
using std::vector;

class StrUtil
{
private:
    static vector< string >& str_split( const string& str, char delim,
            vector< string >& elems );

public:
    static vector< string > str_split( const string& str, char delim );
    static string remove_lf( string str );
};
