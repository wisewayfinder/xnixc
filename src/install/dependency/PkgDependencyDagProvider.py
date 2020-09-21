from abc import abstractmethod
from collections import deque
from typing import Set, Deque

from src.install.PkgCatalog import PkgCatalog
from src.install.PkgCatalogAwareness import PkgCatalogAwareness
from src.utils.dag.Dag import Dag


class PkgDependencyDagProvider(PkgCatalogAwareness):
    @abstractmethod
    def provide_dependency_dag(self) -> Dag[PkgCatalog]:
        raise NotImplementedError

    def aware_pkg_catalogs(self) -> Set[PkgCatalog]:
        aware_set: Set[PkgCatalog] = set()
        check_queue: Deque[PkgCatalog] = deque()
        dependency_dag = self.provide_dependency_dag()
        for node in dependency_dag.root_nodes():
            check_queue.append(node)
        while check_queue:
            item = check_queue.popleft()
            downstreams = dependency_dag.get_downstreams(item)
            for downstream in downstreams:
                check_queue.append(downstream)
            aware_set.add(item)

        return aware_set
