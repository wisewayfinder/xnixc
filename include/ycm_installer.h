#include <string>
#include <vector>

using std::string;
using std::vector;

class YcmInstaller
{
private:
    static const string extra_conf_path;
    static bool chk_ycm();
    static vector< string > get_sys_header_path( string language );
    static bool set_extra_conf( string language );
    static bool ycm_extra_conf_configure();
    static bool restore_ycm();

public:
    static bool install_ycm();
};
