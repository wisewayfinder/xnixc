from src.install.installer.PkgInstaller import PkgInstaller


class Ubuntu2004VimAirlineInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'VimAirline'

    def install(self) -> None:
        raise NotImplementedError
