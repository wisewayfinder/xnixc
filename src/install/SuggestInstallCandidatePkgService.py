from collections import deque
from typing import Set, Deque

from src.install.PkgCatalog import PkgCatalog
from src.install.check.PkgInstallCheckService import PkgInstallCheckService
from src.install.dependency.PkgDependencyDagProvider import PkgDependencyDagProvider


class SuggestInstallCandidatePkgService:
    @staticmethod
    def suggest(pkg_dependency_dag_provider: PkgDependencyDagProvider,
                pkg_install_check_service: PkgInstallCheckService) -> Set[PkgCatalog]:
        whole_catalogs_to_install = pkg_dependency_dag_provider.provide_dependency_dag()
        installed_check_list: Deque[PkgCatalog] = deque()
        already_installed: Set[PkgCatalog] = set()
        install_candidates: Set[PkgCatalog] = set()
        for install_catalog in whole_catalogs_to_install.root_nodes():
            installed_check_list.append(install_catalog)
        while installed_check_list:
            installed_check_item = installed_check_list.popleft()
            if pkg_install_check_service.execute(installed_check_item):
                for downstream in whole_catalogs_to_install.get_downstreams(installed_check_item):
                    installed_check_list.append(downstream)
                already_installed.add(installed_check_item)
            else:
                if len(list(filter(lambda it: it not in already_installed,
                                   whole_catalogs_to_install.get_upstreams(installed_check_item)))) == 0:
                    if installed_check_item not in already_installed:
                        install_candidates.add(installed_check_item)

        return install_candidates
