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
    def animate_to(self, G: Graph):
        animations1 = []  # store in a list so we can play them all in parallel
        animations1 += [
            self.G[x].animate.move_to(G._layout[x]) for x in self.G._graph.nodes
        ]
        to_remove = [e for e in self.G.target._graph.edges if not G._graph.has_edge(*e)]
        print(to_remove)
        animations1 += [self.G.animate.remove_edges(*to_remove)]
        print(self.G, self.G.target)
        to_add = [e for e in G._graph.edges if not self.G.target._graph.has_edge(*e)]
        print(to_add)
        animations2 = self.G.animate.add_edges(*to_add)
        print(self.G, self.G.target)
        print(self.G.target.edges)

        return Succession(AnimationGroup(*animations1), animations2)

    def root(self):
        p = self.get_all_parents(self.g)
        root = 0
        for i in range(len(p)):
            if p[i] == -1:
                root = i
        return root

    def splay_rotate(self, x):
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
        return self.animate_to(self.rebuild())

    def splay(self, x):
        animations = []
        animations.append(self.G[x].animate.set_color(RED))
        while self.root() != x:
            p = self.get_all_parents(self.g)
            y = p[x]
            z = p[y]
            if y >= 0:
                animations.append(self.splay_rotate(x))
                # if (self.g[z][0] == y) == (self.g[y][0] == x):
                #     animations.append(self.splay_rotate(y))
                # else:
                #     animations.append(self.splay_rotate(x))
        print(len(animations))
        return Succession(*animations)


class SplayAnimation(Scene):
    def construct(self):
        splay = Splay("LRLR")
        self.add(splay)
        self.wait()
        self.play(splay.splay(4))
