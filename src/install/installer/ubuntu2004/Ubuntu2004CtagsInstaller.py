from src.install.installer.PkgInstaller import PkgInstaller


class Ubuntu2004CtagsInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'Ctags'

    def install(self) -> None:
        raise NotImplementedError
