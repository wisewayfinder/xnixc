from unittest import TestCase

from src.install.PkgCatalog import PkgCatalog
from src.install.dependency.PkgDependencyDagProvider import PkgDependencyDagProvider
from src.utils.dag.Dag import Dag


class TestPkgDependencyDagProvider(TestCase):
    def test_aware_dependency_set(self):
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
                dag.add_node(PkgCatalog.VIM_AIRLINE)

                dag.add_node(PkgCatalog.XNIXC)

                dag.connect_edge(PkgCatalog.CLANG, PkgCatalog.CMAKE)
                dag.connect_edge(PkgCatalog.VIM, PkgCatalog.VUNDLE)
                dag.connect_edge(PkgCatalog.GIT, PkgCatalog.VUNDLE)

                dag.connect_edge(PkgCatalog.CLANG, PkgCatalog.YCM)
                dag.connect_edge(PkgCatalog.VUNDLE, PkgCatalog.YCM)
                dag.connect_edge(PkgCatalog.VUNDLE, PkgCatalog.VIM_AIRLINE)

                dag.connect_edge(PkgCatalog.YCM, PkgCatalog.XNIXC)
                dag.connect_edge(PkgCatalog.VIM_AIRLINE, PkgCatalog.XNIXC)

                return dag

        dag_provider = MockPkgDependencyDagProvider()
        dependency_set = dag_provider.aware_pkg_catalogs()
        self.assertEqual(
            {PkgCatalog.CLANG, PkgCatalog.VIM, PkgCatalog.GIT, PkgCatalog.CTAGS, PkgCatalog.CMAKE,
             PkgCatalog.VUNDLE, PkgCatalog.YCM, PkgCatalog.VIM_AIRLINE, PkgCatalog.XNIXC},
            dependency_set
        )
