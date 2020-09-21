from src.install.installer.PkgInstaller import PkgInstaller


class Ubuntu2004TagListInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'TagList'

    def install(self) -> None:
        raise NotImplementedError
