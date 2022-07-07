from dataclasses import dataclass
from queue import Queue
from random import randrange
from time import perf_counter
from typing import List, Set, Tuple, Dict

import numpy as np
import numpy.typing as npt

from matplotlib import pyplot as plt


inf = (1 << 64) - 1;

@dataclass
class Edge:
    u: int
    v: int
    cap: int
    cost: int
    flow: int = 0
    blocked: int = 0

'''
flow going through forward edge inside a node 
implies that all adjacent nodes in padded region 
must not accept flow

the blocker function will block those edges
if flow goes through reverse edge, it undoes the decision
hence all blocked nodes must be unblocked 

since multiple nodes can block a single node, we must keep 
track of the numbers as well '''
class MCMF:
    def __init__(s, n: int, padding: int):
        s.n = n
        s.src = -1
        s.sink = -1
        s.padding = padding
        
        s.g: List[List[int]] = [[] for _ in range(n)]
        s.edges: List[Edge] = []
        s.pashe: List[List[int]] = []

        s.prev: List[int] = [-1 for _ in range(n)]

        s.inq: List[bool] = [] 
        s.dis: List[int] = [] 

    def blocker(s, e: int):
        dl = 1 - 2 * (e & 1)
        e -= (e & 1);
        Q = Queue()
        vis: Dict[int, int] = {}

        Q.put(e)
        vis[e] = 0

        while not Q.empty():
            cur = Q.get()
            s.edges[cur].blocked += dl
            for nxt in s.pashe[cur]:
                if nxt not in vis and vis[cur] < s.padding:
                    vis[nxt] = vis[cur] + 1
                    Q.put(nxt)


    def add_edge(s, u: int, v: int, cap: int, cost: int):
        s.g[u].append(len(s.edges))
        edges.append(Edge(u, v, cap, cost))

        s.g[v].append(len(s.edges))
        edges.append(Edge(v, u, 0, -cost))

        s.pashe.append([])
        s.pashe.append([])
        return len(edges) - 2

    def spfa(s) -> bool:
        s.dis = [inf for _ in range(s.n)]
        s.inq = [False for _ in range(s.n)]

        s.dis[s.src] = 0
        s.prev[s.src] = -1

        Q = Queue()
        Q.put(s.src)
        s.inq[s.src] = True

        while not Q.empty(): 
            u = Q.get()
            for e in enumerate(g[u]):
                if s.edges[blocked] == 0 and s.edges[e].cap > s.edges[e].flow and s.dis[s.edges[e].v] > s.dis[u] + s.edges[e].cost:
                    s.dis[s.edges[e].v] = s.dis[u] + s.edges[e].cost
                    s.prev[s.edges[e].v] = e
                    if not s.inq[s.edges[e].v]:
                        s.inq[s.edges[e].v] = True
                        Q.put(s.edges[e].v)
            s.inq[u] = False
        return s.dis[sink] != inf

    def solve(s, src: int, sink: int) -> Tuple[int, int]:
        s.src = src
        s.sink = sink
        s.flow = 0
        s.cost = 0
        while s.spfa():
            bottleneck = inf
            cur = s.prev[sink]
            while cur != -1:
                bottleneck = min(bottleneck, s.edges[cur].cap - s.edges[cur].flow)
                cur = s.prev[s.edges[cur].u]

            cur = s.prev[sink]
            while cur != -1:
                s.edges[cur].flow += bottleneck
                s.edges[cur ^ 1].flow -= bottleneck
                blocker(cur)
                cur = s.prev[s.edges[cur].u]

            s.cost += bottleneck * s.dis[sink]
            s.flow += bottleneck
        return (s.flow, s.cost)


class DroneSender:
    def __init__(self, n: int,
                Edges: List[npt.NDArray[np.int_]],
                start: List[int],
                finish: List[int],
                padding: int = 0):
        self.n = n
        self.source = 0
        self.sink = 2*n + 1
        self.padding = padding
        self.G = MCMF(2*n + 2, padding)
        self.nodecap = [-1 for _ in range(n)]
        self.Edges = Edges

        for i in range(n):
            self.nodecap[i] = self.G.add_edge(self.entry(i), self.exit(i), 1, 0)

        for u, v, w in self.Edges:
            print(u, v);
            self.G.add_edge(self.exit(u), self.entry(v), 1, w)
            self.G.add_edge(self.exit(v), self.entry(u), 1, w)
            
            self.G.pashe[self.nodecap[u]].append(self.nodecap[v])
            self.G.pashe[self.nodecap[v]].append(self.nodecap[u])

        for u in start:
            self.G.add_edge(self.source, self.entry(u), 1, 0)
        
        for v in finish:
            self.G.add_edge(self.exit(v), self.sink, 1, 0)

        print('Crunching...')
        st_time = perf_counter()
        sent, cost = self.G.solve(self.source, self.sink)
        ed_time = perf_counter()
        print(f'Done in {ed_time - st_time}!')
        self.status = sent == len(start)
        self.cost = cost

    def path(self, node: int) -> List[int]:
        node = self.exit(node)
        path = []
        while node < self.sink:
            path.append((node + 1) // 2)
            node = self.next(node)
        return path

    @staticmethod
    def entry(node: int) -> int:
        return node * 2 - 1
    
    @staticmethod
    def exit(node: int) -> int:
        return node * 2

    def next(self, node: int) -> int:
        for x in self.G.g[node]:
            if self.G.edges[x].flow > 0:
                return self.G.edges[x].v + 1
        return self.sink

if __name__ == '__main__':
    n = 10
    edges = [np.array((1, 2, 1)), np.array((2, 3, 1)), np.array((4, 5, 1)), np.array((5, 6, 1)), np.array((7, 8, 1)), np.array((8, 9, 1))]
    start = [1, 4, 7]
    end = [3, 6, 9]
    pp = DroneSender(n, edges, start, end)