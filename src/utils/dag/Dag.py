from collections import deque
from typing import Generic, TypeVar, List, Dict, Optional, Deque

T = TypeVar('T')


class Dag(Generic[T]):
    def __init__(self) -> None:
        self.__dag_edges: List[List[Optional[bool]]] = []
        self.__dag_index_map: Dict[int, T] = {}
        self.__dag_index_invert_map: Dict[T, int] = {}
        super().__init__()

    def add_node(self, _id: T):
        if _id is None:
            raise TypeError('None is not allowed to add_root_node')
        if _id in self.__dag_index_invert_map:
            raise ValueError(f"{_id} is already in DAG")

        all_nodes_cnt = len(self.__dag_edges)
        for start_node_idx in range(0, all_nodes_cnt):
            self.__dag_edges[start_node_idx].append(None)
        self.__dag_edges.append(
            list(map(lambda _: None, range(0, all_nodes_cnt + 1))))
        self.__dag_index_map[all_nodes_cnt] = _id
        self.__dag_index_invert_map[_id] = all_nodes_cnt

    def connect_edge(self, parent_id: T, child_id: T):
        if parent_id is None:
            raise TypeError('None is not allowed in parent_id to connect_edge')
        if child_id is None:
            raise TypeError('None is not allowed in child_id to connect_edge')
        if parent_id == child_id:
            raise ValueError(f'both node are same, {parent_id}')
        if parent_id not in self.__dag_index_invert_map:
            raise KeyError(f'parent_id {parent_id} is not exist in DAG')
        if child_id not in self.__dag_index_invert_map:
            raise KeyError(f'child_id {child_id} is not exist in DAG')
        if self.__dag_edges[self.__dag_index_invert_map[parent_id]][self.__dag_index_invert_map[child_id]] is True:
            raise ValueError(f'parent {parent_id} to child {child_id} edge already exist')
        if self.__dag_edges[self.__dag_index_invert_map[parent_id]][self.__dag_index_invert_map[child_id]] is False:
            raise ValueError(f'reverse connection child {child_id} to parent {parent_id} is already exist')
        self.__check_cycle(parent_id, child_id)
        self.__operate_connect(parent_id, child_id)

    def root_nodes(self) -> List[T]:
        result: List[T] = []
        for idx in range(0, len(self.__dag_edges)):
            if len(list(filter(lambda it: it is False, self.__dag_edges[idx]))) == 0:
                result.append(self.__dag_index_map[idx])

        return result

    def get_upstreams(self, _id: T) -> List[T]:
        node_idx = self.__dag_index_invert_map[_id]
        result: List[T] = []
        for start_idx in range(0, len(self.__dag_edges)):
            if self.__dag_edges[start_idx][node_idx]:
                result.append(self.__dag_index_map[start_idx])
        return result

    def get_downstreams(self, _id: T) -> List[T]:
        node_idx = self.__dag_index_invert_map[_id]
        result: List[T] = []
        for end_idx in range(0, len(self.__dag_edges)):
            if self.__dag_edges[node_idx][end_idx]:
                result.append(self.__dag_index_map[end_idx])
        return result

    def __check_cycle(self, parent_id: T, child_id: T):
        checking_queue: Deque[T] = deque()
        checking_queue.append(parent_id)

        while checking_queue:
            candidate_ancestor_id = checking_queue.popleft()
            if candidate_ancestor_id == child_id:
                raise ValueError(f'child ${child_id} is in cycle')
            candidate_ancestor_id_idx = self.__dag_index_invert_map[candidate_ancestor_id]
            for start_idx in range(0, len(self.__dag_edges)):
                if self.__dag_edges[start_idx][candidate_ancestor_id_idx]:
                    checking_queue.append(self.__dag_index_map[start_idx])

    def __operate_connect(self, parent_id: T, child_id: T):
        start_idx = self.__dag_index_invert_map[parent_id]
        end_idx = self.__dag_index_invert_map[child_id]
        self.__dag_edges[start_idx][end_idx] = True
        self.__dag_edges[end_idx][start_idx] = False
