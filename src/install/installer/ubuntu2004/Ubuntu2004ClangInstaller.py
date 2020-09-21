import os

from src.install.installer.PkgInstaller import PkgInstaller


# https://apt.llvm.org/
class Ubuntu2004ClangInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'Clang'

    def install(self) -> None:
        os.system('bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"')
