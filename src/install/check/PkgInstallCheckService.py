from abc import ABCMeta

from src.install.PkgCatalogAwareService import PkgCatalogAwareService


class PkgInstallCheckService(PkgCatalogAwareService[None, bool], metaclass=ABCMeta):
    pass
