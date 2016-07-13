#include <string>

using std::string;

class ClangInstaller
{
public:
    static bool check_clang();
    static string get_clang_path( string lang );
    static string get_clang_cmd( string lang );
    static bool install_clang();
};
