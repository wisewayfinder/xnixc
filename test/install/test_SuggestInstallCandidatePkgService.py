from typing import Set, Dict, Callable
from unittest import TestCase

from src.install.PkgCatalogAwareService import T
from src.install.SuggestInstallCandidatePkgService import SuggestInstallCandidatePkgService
from src.install.PkgCatalog import PkgCatalog
from src.install.check.PkgInstallCheckService import PkgInstallCheckService
from src.install.dependency.PkgDependencyDagProvider import PkgDependencyDagProvider
from src.utils.dag.Dag import Dag


class TestSuggestInstallCandidatePkgService(TestCase):
    def test_generate(self):
        class MockPkgDependencyDagProvider(PkgDependencyDagProvider):
            def provide_dependency_dag(self) -> Dag[PkgCatalog]:
                dag: Dag[PkgCatalog] = Dag()

                dag.add_node(PkgCatalog.CLANG)
                dag.add_node(PkgCatalog.VIM)
                dag.add_node(PkgCatalog.GIT)
                dag.add_node(PkgCatalog.CTAGS)

                dag.add_node(PkgCatalog.CMAKE)
                dag.add_node(PkgCatalog.VUNDLE)

                dag.add_node(PkgCatalog.YCM)
                dag.add_node(PkgCatalog.NERD_TREE)
                dag.add_node(PkgCatalog.CSCOPE)
                dag.add_node(PkgCatalog.TAG_LIST)
                dag.add_node(PkgCatalog.EASY_TAG)
                dag.add_node(PkgCatalog.VIM_AIRLINE)

                dag.add_node(PkgCatalog.XNIXC)

                dag.connect_edge(PkgCatalog.CLANG, PkgCatalog.CMAKE)
                dag.connect_edge(PkgCatalog.VIM, PkgCatalog.VUNDLE)
                dag.connect_edge(PkgCatalog.GIT, PkgCatalog.VUNDLE)

                dag.connect_edge(PkgCatalog.CLANG, PkgCatalog.YCM)
                dag.connect_edge(PkgCatalog.VUNDLE, PkgCatalog.YCM)
                dag.connect_edge(PkgCatalog.VUNDLE, PkgCatalog.NERD_TREE)
                dag.connect_edge(PkgCatalog.VUNDLE, PkgCatalog.CSCOPE)
                dag.connect_edge(PkgCatalog.VUNDLE, PkgCatalog.TAG_LIST)
                dag.connect_edge(PkgCatalog.VUNDLE, PkgCatalog.EASY_TAG)
                dag.connect_edge(PkgCatalog.VUNDLE, PkgCatalog.VIM_AIRLINE)

                dag.connect_edge(PkgCatalog.YCM, PkgCatalog.XNIXC)
                dag.connect_edge(PkgCatalog.NERD_TREE, PkgCatalog.XNIXC)
                dag.connect_edge(PkgCatalog.CSCOPE, PkgCatalog.XNIXC)
                dag.connect_edge(PkgCatalog.TAG_LIST, PkgCatalog.XNIXC)
                dag.connect_edge(PkgCatalog.EASY_TAG, PkgCatalog.XNIXC)
                dag.connect_edge(PkgCatalog.VIM_AIRLINE, PkgCatalog.XNIXC)

                return dag

        class MockPkgInstallCheckService(PkgInstallCheckService):
            def _define_behavior(self) -> Dict[PkgCatalog, Callable[[None], bool]]:
                result: Dict[PkgCatalog, Callable[[None], bool]] = {}
                for pkg_catalog in PkgCatalog:
                    if pkg_catalog == PkgCatalog.CLANG or pkg_catalog == PkgCatalog.VIM:
                        result[pkg_catalog] = lambda _: True
                    else:
                        result[pkg_catalog] = lambda _: False
                return result

        res = SuggestInstallCandidatePkgService.suggest(
            MockPkgDependencyDagProvider(),
            MockPkgInstallCheckService()
        )
        self.assertEqual(len(res), 3)
        self.assertTrue(PkgCatalog.GIT in res)
        self.assertTrue(PkgCatalog.CTAGS in res)
        self.assertTrue(PkgCatalog.CMAKE in res)
