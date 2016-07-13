#include <string>

using std::string;

class XnixcInstaller
{
private:
    static bool set_makefile( const string lang );

public:
    static bool install_xnixc();
};
