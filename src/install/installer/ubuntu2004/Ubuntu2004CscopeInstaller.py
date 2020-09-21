from src.install.installer.PkgInstaller import PkgInstaller


class Ubuntu2004CscopeInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'Cscope'

    def install(self) -> None:
        raise NotImplementedError
