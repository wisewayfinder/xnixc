from abc import abstractmethod, ABC
from typing import Set

from src.install.PkgCatalog import PkgCatalog


class PkgCatalogAwareness(ABC):
    @abstractmethod
    def aware_pkg_catalogs(self) -> Set[PkgCatalog]:
        raise NotImplementedError
