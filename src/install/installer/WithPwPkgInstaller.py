import os
from abc import ABCMeta
from typing import Optional

from src.install.installer.PkgInstaller import PkgInstaller
from src.utils.os.SudoRunner import SudoRunner


class WithPwPkgInstaller(PkgInstaller, metaclass=ABCMeta):
    def __init__(self, sudo_password: Optional[str] = None) -> None:
        self.__sudo_pw: Optional[str] = sudo_password
        super().__init__()

    def _sudo_with_pw(self, cmd: str):
        os.system(cmd) if self.__sudo_pw is None else SudoRunner.run(cmd, self.__sudo_pw)
