from abc import abstractmethod
from typing import TypeVar, Dict, Callable, Set, Generic

from src.install.PkgCatalog import PkgCatalog
from src.install.PkgCatalogAwareness import PkgCatalogAwareness

T = TypeVar('T')
R = TypeVar('R')


class PkgCatalogAwareService(Generic[T, R], PkgCatalogAwareness):
    def __init__(self) -> None:
        self.__aware_behavior_map: Dict[PkgCatalog, Callable[[T], R]] = self._define_behavior()
        super().__init__()

    def execute(self, pkg_catalog: PkgCatalog, t: T = None) -> R:
        if pkg_catalog not in self.aware_pkg_catalogs():
            raise ValueError(f"unknown pkg_catalog {pkg_catalog}")
        return self.__aware_behavior_map[pkg_catalog](t)

    def aware_pkg_catalogs(self) -> Set[PkgCatalog]:
        return set(self.__aware_behavior_map.keys())

    @abstractmethod
    def _define_behavior(self) -> Dict[PkgCatalog, Callable[[T], R]]:
        pass
