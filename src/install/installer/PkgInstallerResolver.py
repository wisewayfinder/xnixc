from abc import ABCMeta

from src.install.PkgCatalogAwareService import PkgCatalogAwareService
from src.install.installer.PkgInstaller import PkgInstaller


class PkgInstallerResolver(PkgCatalogAwareService[None, PkgInstaller], metaclass=ABCMeta):
    pass
