from src.install.installer.PkgInstaller import PkgInstaller


class Ubuntu2004CMakeInstaller(PkgInstaller):
    def one_line_description(self) -> str:
        return 'CMake'

    def install(self) -> None:
        raise NotImplementedError
