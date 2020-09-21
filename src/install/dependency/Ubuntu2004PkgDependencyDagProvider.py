from src.install.PkgCatalog import PkgCatalog
from src.install.dependency.PkgDependencyDagProvider import PkgDependencyDagProvider
from src.utils.dag.Dag import Dag


class Ubuntu2004PkgDependencyDagProvider(PkgDependencyDagProvider):
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
