from src.install.installer.PkgInstaller import PkgInstaller


class Ubuntu2004ClangInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'Clang'

    def install(self) -> None:
        raise NotImplementedError