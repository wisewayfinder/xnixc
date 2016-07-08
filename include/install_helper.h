#include <string>

using std::string;

class InstallHelper
{
private:
    static const string UBUNTU;
    static const string MAC;
    static const string UNKNOWN;

public:
    const string xnix_cmd_exec( const char* cmd );
    const string get_os();
};
