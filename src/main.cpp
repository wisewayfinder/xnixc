#include <iostream>
#include "install_helper.h"

using std::cout;
using std::endl;

int main()
{
    InstallHelper install_helper;

    cout << install_helper.get_os() << endl;

    return(0);
}
