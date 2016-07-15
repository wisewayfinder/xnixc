#include <string>

using std::string;

class VimManager
{
private:
    static bool check_vundle();
    static bool vimrc_configure();
    static bool vundle_install();
    static bool plugin_install();

public:
    static bool vim_configure();
};
