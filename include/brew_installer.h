#include <string>

using std::string;

class BrewInstaller
{
public:
    static bool chk_brew();
    static bool chk_pack( const string& pack_name );
    static bool install_brew();
};
