#include <string>

using std::string;

class InstallHelper
{
private:
    InstallHelper();
    static bool instance_poped;
    static InstallHelper* instance;

    static const string UBUNTU;
    static const string MAC;
    static const string UNKNOWN;


public:
    virtual ~InstallHelper();
    static InstallHelper* get_instance();

    const string xnix_cmd_exec( const char* cmd );
    const string get_os();
};
