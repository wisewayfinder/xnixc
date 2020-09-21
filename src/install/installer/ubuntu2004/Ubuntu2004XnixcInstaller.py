from src.install.installer.PkgInstaller import PkgInstaller


class Ubuntu2004XnixcInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'xninxc'

    def install(self) -> None:
        raise NotImplementedError
