# %% splay animation
from manim import *
import networkx as nx
import copy


class Splay(VMobject):
    def __init__(self, g, **kwargs):
        super().__init__(**kwargs)
        # store an internal adj list specific to maintain binary tree structure
        if isinstance(g, str):
            self.g = self.from_str(g)
        else:
            self.g = g
        self.G = self.build_graph()
        self.add(self.G)
        self.G.generate_target(False)

    @staticmethod
    def from_str(s):
        g = [[-1, -1]]
        for i in range(len(s)):
            if s[i] == "L":
                g[-1][0] = i + 1
            else:  # s[i] == 'R'
                g[-1][1] = i + 1
            g.append([-1, -1])
        return g

    # gets array of parents for this graph
    def get_all_parents(self, g):
        p = [-1] * len(g)
        for i, [l, r] in enumerate(g):
            if l >= 0:
                p[l] = i
            if r >= 0:
                p[r] = i
        return p

    def rebuild(self):
        layout = {}
        G = nx.Graph()

        def dfs(u, d):
            nonlocal layout
            if self.g[u][0] >= 0:
                G.add_edge(u, self.g[u][0])
                dfs(self.g[u][0], d - 1)
            x, _, z = self.G[u].get_center()
            layout[u] = [x, d, z]
            if self.g[u][1] >= 0:
                G.add_edge(u, self.g[u][1])
                dfs(self.g[u][1], d - 1)

        dfs(self.root(), 2)
        return Graph(list(G.nodes), list(G.edges), layout=layout, labels=True)

    def build_graph(self):
        g = self.g
        G = nx.Graph()
        lt = {}

        x = 0

        def dfs(u, d):
            nonlocal x
            nonlocal G
            G.add_node(u)
            if g[u][0] >= 0:
                G.add_edge(u, g[u][0])
                dfs(g[u][0], d - 1)
            lt[u] = [x, d, 0]
            x += 1
            if g[u][1] >= 0:
                G.add_edge(u, g[u][1])
                dfs(g[u][1], d - 1)

        dfs(0, 2)
        return Graph(list(G.nodes), list(G.edges), layout=lt, labels=True)

    # animates current graph into graph G
    def animate_to(self, G: Graph, scene: Scene):
        animations = [self.G[x].animate.move_to(G._layout[x]) for x in self.G._graph.nodes]
        to_remove = [e for e in self.G._graph.edges if not G._graph.has_edge(*e)]
        if len(to_remove) > 0: animations += [self.G.animate.remove_edges(*to_remove)]
        scene.play(animations)
        to_add = [e for e in G._graph.edges if not self.G._graph.has_edge(*e)]
        if len(to_add) > 0: scene.play(self.G.animate.add_edges(*to_add))

    def root(self):
        p = self.get_all_parents(self.g)
        root = 0
        for i in range(len(p)):
            if p[i] == -1:
                root = i
        return root

    def splay_rotate(self, x, scene: Scene):
        p = self.get_all_parents(self.g)
        y = p[x]
        z = p[y]
        if z >= 0:
            if self.g[z][0] == y:
                self.g[z][0] = x
            else:
                self.g[z][1] = x
        if self.g[y][0] == x:
            self.g[y][0] = self.g[x][1]
            self.g[x][1] = y
        else:
            self.g[y][1] = self.g[x][0]
            self.g[x][0] = y
        return self.animate_to(self.rebuild(), scene)

    def splay(self, x, scene: Scene):
        scene.play(self.G[x].animate.set_color(RED))
        while self.root() != x:
            p = self.get_all_parents(self.g)
            y = p[x]
            z = p[y]
            if y >= 0:
              if (self.g[z][0] == y) == (self.g[y][0] == x):
                  self.splay_rotate(y, scene)
              else:
                  self.splay_rotate(x, scene)
            self.splay_rotate(x, scene)


class SplayAnimation(Scene):
    def construct(self):
        splay1 = Splay("LRLR")
        splay2 = Splay("RRRR")
        self.add(splay1.shift(LEFT * 4))
        self.add(splay2.next_to(splay1, RIGHT))
        splay1.splay(4, self)
