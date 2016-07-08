#include <string>

using std::string;

class InstallHelper
{
private:
    InstallHelper();

public:
    static const string UBUNTU;
    static const string MAC;
    static const string UNKNOWN;

    static const string xnix_cmd_exec( const char* cmd );
    static const string get_os();
    static bool terminate( string reason = string("") );
};
