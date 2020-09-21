from typing import Dict, Callable

from src.install.PkgCatalog import PkgCatalog
from src.install.installer.PkgInstaller import PkgInstaller
from src.install.installer.PkgInstallerResolver import PkgInstallerResolver
from src.install.installer.ubuntu2004.Ubuntu2004CMakeInstaller import Ubuntu2004CMakeInstaller
from src.install.installer.ubuntu2004.Ubuntu2004ClangInstaller import Ubuntu2004ClangInstaller
from src.install.installer.ubuntu2004.Ubuntu2004CscopeInstaller import Ubuntu2004CscopeInstaller
from src.install.installer.ubuntu2004.Ubuntu2004CtagsInstaller import Ubuntu2004CtagsInstaller
from src.install.installer.ubuntu2004.Ubuntu2004EasyTagInstaller import Ubuntu2004EasyTagInstaller
from src.install.installer.ubuntu2004.Ubuntu2004GitInstaller import Ubuntu2004GitInstaller
from src.install.installer.ubuntu2004.Ubuntu2004NerdTreeInstaller import Ubuntu2004NerdTreeInstaller
from src.install.installer.ubuntu2004.Ubuntu2004TagListInstaller import Ubuntu2004TagListInstaller
from src.install.installer.ubuntu2004.Ubuntu2004VimAirlineInstaller import Ubuntu2004VimAirlineInstaller
from src.install.installer.ubuntu2004.Ubuntu2004VimInstaller import Ubuntu2004VimInstaller
from src.install.installer.ubuntu2004.Ubuntu2004VundleInstaller import Ubuntu2004VundleInstaller
from src.install.installer.ubuntu2004.Ubuntu2004XnixcInstaller import Ubuntu2004XnixcInstaller
from src.install.installer.ubuntu2004.Ubuntu2004YcmInstaller import Ubuntu2004YcmInstaller


class Ubuntu2004PkgInstallerResolver(PkgInstallerResolver):
    def _define_behavior(self) -> Dict[PkgCatalog, Callable[[None], PkgInstaller]]:
        return {
            PkgCatalog.CLANG: lambda _: Ubuntu2004ClangInstaller(),
            PkgCatalog.VIM: lambda _: Ubuntu2004VimInstaller(),
            PkgCatalog.GIT: lambda _: Ubuntu2004GitInstaller(),
            PkgCatalog.CTAGS: lambda _: Ubuntu2004CtagsInstaller(),
            PkgCatalog.CMAKE: lambda _: Ubuntu2004CMakeInstaller(),
            PkgCatalog.VUNDLE: lambda _: Ubuntu2004VundleInstaller(),
            PkgCatalog.YCM: lambda _: Ubuntu2004YcmInstaller(),
            PkgCatalog.NERD_TREE: lambda _: Ubuntu2004NerdTreeInstaller(),
            PkgCatalog.CSCOPE: lambda _: Ubuntu2004CscopeInstaller(),
            PkgCatalog.TAG_LIST: lambda _: Ubuntu2004TagListInstaller(),
            PkgCatalog.EASY_TAG: lambda _: Ubuntu2004EasyTagInstaller(),
            PkgCatalog.VIM_AIRLINE: lambda _: Ubuntu2004VimAirlineInstaller(),
            PkgCatalog.XNIXC: lambda _: Ubuntu2004XnixcInstaller(),
        }