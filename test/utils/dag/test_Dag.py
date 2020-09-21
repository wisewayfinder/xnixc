from typing import Optional
from unittest import TestCase

from src.utils.dag.Dag import Dag


class TestDag(TestCase):
    def test_add_node_fail_because_try_with_None(self):
        dag = Dag()
        self.assertRaises(TypeError, lambda: dag.add_node(None))

    def test_add_node_fail_because_try_with_duplicate_node(self):
        dag: Dag[int] = Dag()
        dup_val = 1
        dag.add_node(dup_val)
        self.assertRaises(ValueError, lambda: dag.add_node(dup_val))

    def test_add_node_success(self):
        dag: Dag[str] = Dag()
        dag.add_node('1')
        dag.add_node('2')
        dag.add_node('3')

        self.assertEqual(['1', '2', '3'], dag.root_nodes())

    def test_root_nodes(self):
        dag: Dag[int] = Dag()
        dag.add_node(1)
        dag.add_node(2)
        dag.add_node(3)
        dag.connect_edge(1, 2)

        self.assertEqual([1, 3], dag.root_nodes())

    def test_connect_edge_fail_because_try_with_None(self):
        dag: Dag[Optional[int]] = Dag()
        dag.add_node(1)
        dag.add_node(2)
        self.assertRaises(TypeError, lambda: dag.connect_edge(None, 1))
        self.assertRaises(TypeError, lambda: dag.connect_edge(2, None))

    def test_connect_edge_fail_because_parent_and_child_are_same(self):
        dag: Dag[int] = Dag()
        dag.add_node(1)
        dag.add_node(2)
        self.assertRaises(ValueError, lambda: dag.connect_edge(1, 1))

    def test_connect_edge_fail_because_node_not_exist(self):
        dag: Dag[int] = Dag()
        self.assertRaises(KeyError, lambda: dag.connect_edge(1, 2))

        dag.add_node(1)
        self.assertRaises(KeyError, lambda: dag.connect_edge(1, 2))

    def test_connect_edge_fail_because_edge_already_exist(self):
        dag: Dag[int] = Dag()
        dag.add_node(1)
        dag.add_node(2)
        dag.connect_edge(1, 2)
        self.assertRaises(ValueError, lambda: dag.connect_edge(1, 2))

    def test_append_node_fail_because_it_make_cycle(self):
        dag: Dag[int] = Dag()
        dag.add_node(1)
        dag.add_node(2)
        dag.connect_edge(1, 2)
        self.assertRaises(ValueError, lambda: dag.connect_edge(2, 1))

        dag.add_node(3)
        dag.connect_edge(2, 3)
        self.assertRaises(ValueError, lambda: dag.connect_edge(3, 1))
        self.assertRaises(ValueError, lambda: dag.connect_edge(3, 2))

        dag.add_node(4)
        dag.connect_edge(3, 4)
        self.assertRaises(ValueError, lambda: dag.connect_edge(3, 2))
        self.assertRaises(ValueError, lambda: dag.connect_edge(4, 2))
        self.assertRaises(ValueError, lambda: dag.connect_edge(4, 1))

    def test_get_upstreams(self):
        dag: Dag[int] = Dag()
        dag.add_node(1)
        self.assertEqual([], dag.get_upstreams(1))

        dag.add_node(2)
        dag.connect_edge(1, 2)
        self.assertEqual([1], dag.get_upstreams(2))

        dag.add_node(3)
        dag.connect_edge(3, 2)
        self.assertEqual([1, 3], dag.get_upstreams(2))

    def test_get_downstreams(self):
        dag: Dag[int] = Dag()
        dag.add_node(1)
        self.assertEqual([], dag.get_downstreams(1))

        dag.add_node(2)
        dag.connect_edge(1, 2)
        self.assertEqual([2], dag.get_downstreams(1))

        dag.add_node(3)
        dag.connect_edge(1, 3)
        self.assertEqual([2, 3], dag.get_downstreams(1))
