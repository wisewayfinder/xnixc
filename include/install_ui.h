#include <string>
#include <vector>

using std::string;
using std::vector;

struct CmdInfo
{
    string cmd_name;
    bool (*check_func)();
    bool (*install_func)();

    CmdInfo( const string _cmd_name, bool (*_check_func)(),
            bool (*_install_func)() )
        : cmd_name( _cmd_name ), check_func( _check_func ),
        install_func( _install_func ) {}
};

class InstallUi
{
private:
    vector< CmdInfo > cmd_list;

    bool init_cmd_list();
    bool draw_cmds();
    bool install_cmd( int cmd_num );

public:
    InstallUi();
    bool draw_ui();
};
