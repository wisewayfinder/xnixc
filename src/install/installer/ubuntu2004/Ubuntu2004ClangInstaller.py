import os

from src.install.installer.PkgInstaller import PkgInstaller


# https://apt.llvm.org/
class Ubuntu2004ClangInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'Clang'

    def install(self) -> None:
        os.system(f"mkdir {Ubuntu2004ClangInstaller.__tmp_path()}")
        os.system(f"cd {Ubuntu2004ClangInstaller.__tmp_path()} && wget https://apt.llvm.org/llvm.sh")
        os.system(f"cd {Ubuntu2004ClangInstaller.__tmp_path()} && chmod +x llvm.sh")
        os.system(f"cd {Ubuntu2004ClangInstaller.__tmp_path()} && sudo ./llvm.sh {self.clang_version()}")
        os.system(f"rm -rf {Ubuntu2004ClangInstaller.__tmp_path()}")

    @staticmethod
    def clang_version() -> int:
        return 11

    @staticmethod
    def __tmp_path() -> str:
        return './.tmp'
