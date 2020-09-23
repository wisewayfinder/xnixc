import os
from typing import Optional

from src.install.installer.WithPwPkgInstaller import WithPwPkgInstaller


class Ubuntu2004ClangInstaller(WithPwPkgInstaller):
    def __init__(self, sudo_password: Optional[str] = None) -> None:
        super().__init__(sudo_password)

    def one_line_description(self) -> str:
        return 'Clang'

    def install(self):
        # https://apt.llvm.org/
        os.system(f"mkdir {Ubuntu2004ClangInstaller.__tmp_path()}")
        os.system(f"cd {Ubuntu2004ClangInstaller.__tmp_path()} && wget https://apt.llvm.org/llvm.sh")
        os.system(f"cd {Ubuntu2004ClangInstaller.__tmp_path()} && chmod +x llvm.sh")
        self._sudo_with_pw(f"cd {Ubuntu2004ClangInstaller.__tmp_path()} && sudo ./llvm.sh {Ubuntu2004ClangInstaller.clang_version()}")
        os.system(f"rm -rf {Ubuntu2004ClangInstaller.__tmp_path()}")

    @staticmethod
    def clang_version() -> int:
        return 11

    @staticmethod
    def __tmp_path() -> str:
        return './.tmp'
