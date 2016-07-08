#include <string>

using std::string; 

class ClangInstaller
{
private:
    static bool check_clang();

public:
    static bool install_clang();
};
