import sys
from src.install.installer.PkgInstaller import PkgInstaller


class ExitInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'exit'

    def install(self) -> None:
        sys.exit()
