#include <string>

using std::string;

class ClangInstaller
{
private:
    static bool find_clang_cmd( const string& str, const string& lang );

public:
    static string get_clang_path( const string& lang );
    static string get_clang_cmd( const string& lang );
    static bool check_clang();
    static bool install_clang();
};
