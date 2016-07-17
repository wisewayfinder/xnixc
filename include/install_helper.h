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

    static const string FAILED;

    static const string get_home();
    static const string xnix_cmd_exec( const char* cmd, bool silent = true );
    static const string get_os();
    static void examine_os( string err_msg );
    static bool terminate( string reason = string("") );
};
