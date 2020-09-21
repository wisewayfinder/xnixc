from src.install.installer.PkgInstaller import PkgInstaller


class Ubuntu2004GitInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'Git'

    def install(self) -> None:
        raise NotImplementedError
