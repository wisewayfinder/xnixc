from src.install.installer.PkgInstaller import PkgInstaller


class Ubuntu2004EasyTagInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'EasyTag'

    def install(self) -> None:
        raise NotImplementedError
