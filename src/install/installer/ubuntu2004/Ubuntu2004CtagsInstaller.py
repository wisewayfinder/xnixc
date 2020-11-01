from typing import Optional

from src.install.installer.WithPwPkgInstaller import WithPwPkgInstaller


class Ubuntu2004CtagsInstaller(WithPwPkgInstaller):
    def __init__(self, sudo_password: Optional[str] = None) -> None:
        super().__init__(sudo_password)

    def one_line_description(self) -> str:
        return 'Ctags'

    def install(self) -> None:
        self._sudo_with_pw('sudo apt-get install -y exuberant-ctags')
