import os
from typing import Optional

from src.install.installer.PkgInstaller import PkgInstaller


# https://apt.llvm.org/
from src.utils.os.SudoRunner import SudoRunner


class Ubuntu2004ClangInstaller(PkgInstaller):
    def __init__(self, sudo_password: Optional[str] = None) -> None:
        self.__sudo_pw: Optional[str] = sudo_password
        super().__init__()

    def one_line_description(self) -> str:
        return 'Clang'

    def install(self):
        os.system(f"mkdir {Ubuntu2004ClangInstaller.__tmp_path()}")
        os.system(f"cd {Ubuntu2004ClangInstaller.__tmp_path()} && wget https://apt.llvm.org/llvm.sh")
        os.system(f"cd {Ubuntu2004ClangInstaller.__tmp_path()} && chmod +x llvm.sh")
        llvm_install_cmd = f"cd {Ubuntu2004ClangInstaller.__tmp_path()} && sudo ./llvm.sh {Ubuntu2004ClangInstaller.clang_version()}"
        if self.__sudo_pw is None:
            os.system(llvm_install_cmd)
        else:
            SudoRunner.run(llvm_install_cmd, self.__sudo_pw)
        os.system(f"rm -rf {Ubuntu2004ClangInstaller.__tmp_path()}")

    @staticmethod
    def clang_version() -> int:
        return 11

    @staticmethod
    def __tmp_path() -> str:
        return './.tmp'
