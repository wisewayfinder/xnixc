from src.install.installer.PkgInstaller import PkgInstaller


class Ubuntu2004VundleInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'Vundle'

    def install(self) -> None:
        raise NotImplementedError
