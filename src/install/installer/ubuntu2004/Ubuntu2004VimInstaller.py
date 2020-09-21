from src.install.installer.PkgInstaller import PkgInstaller


class Ubuntu2004VimInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        raise NotImplementedError

    def install(self) -> None:
        raise NotImplementedError
