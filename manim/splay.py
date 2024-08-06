# %% splay animation
from manim import *
import networkx as nx

class Splay(Scene):
  def from_str(self, s):
    g = [[-1, -1]]
    for i in range(len(s)):
      if s[i] == 'L':
        g[-1][0] = i + 1
      else: # s[i] == 'R'
        g[-1][1] = i + 1
      g.append([-1, -1])
    return g
  def get_par(self, g):
    p = [-1] * len(g)
    for (i, [l, r]) in enumerate(g):
      if l >= 0: p[l] = i
      if r >= 0: p[r] = i
    return p
  def build_graph(self, g, root, x):
    p = [0] * len(g)
    G = nx.Graph()
    lt = {}
    def dfs(u, d):
      nonlocal x
      nonlocal G
      G.add_node(u);
      if g[u][0] >= 0:
        G.add_edge(u, g[u][0])
        dfs(g[u][0], d - 1)
      p[u] = x
      lt[u] = [x, d, 0]
      x += 1
      if g[u][1] >= 0:
        G.add_edge(u, g[u][1])
        dfs(g[u][1], d - 1)
    dfs(root, 2)
    return Graph(list(G.nodes), list(G.edges), layout=lt, labels=True), g, lt, G
  def animate_between(self, G: Graph, GG: Graph):
    l = []
    print(G._graph.nodes)
    for x in G._graph.nodes:
      assert(x in GG._graph.nodes)
      l.append(G[x].animate.move_to(GG._layout[x]))
    for e in G._graph.edges:
      if e not in GG._graph.edges:
        l.append(G.animate.remove_edges(e))
    print(len(l))
    self.play(l)
    print(G._layout[1])
    ll = []
    for e in GG._graph.edges:
      if e not in G._graph.edges:
        ll.append(G.animate.add_edges(e))
    return ll
  def rotate(self, G: Graph, g, x, l):
    p = self.get_par(g)
    y = p[x]
    z = p[y]
    print("original: ", g, x, y, z)
    if z >= 0:
      if g[z][0] == y:
        g[z][0] = x
      else:
        g[z][1] = x
    if g[y][0] == x:
      g[y][0] = g[x][1]
      g[x][1] = y
    else:
      g[y][1] = g[x][0]
      g[x][0] = y
    p = self.get_par(g)
    root = 0
    for i in range(len(p)):
      if p[i] == -1: root = i
    GG, gg, lt, GGG = self.build_graph(g, root, l)
    print(g, GG._graph.nodes, GG._layout)
    # self.play(G.animate.update_edges(GG))
    # self.play(G.animate.add_edges((y, x), edge_config={"color": RED}))
    l = self.animate_between(G, GG)
    # l += [G.animate.add_edges((y, x))]
    if len(l) > 0: self.play(l)
    return g
  def splay(self, G: Graph, g, x, l):
    self.play(G[x].animate.set_color(RED))
    p = self.get_par(g)
    root = 0
    for i in range(len(p)):
      if p[i] == -1: root = i
    while p[x] >= 0:
      y = p[x]
      z = p[y]
      if z >= 0:
        if (g[z][0] == y) == (g[y][0] == x):
          g = self.rotate(G, g, y, l)
        else:
          g = self.rotate(G, g, x, l)
      g = self.rotate(G, g, x, l)
      p = self.get_par(g)
  def construct(self):
    G, g, _, _ = self.build_graph(self.from_str("LRLR"), 0, -5)
    G1, g1, _, _ = self.build_graph(self.from_str("LRLLR"), 0, 1)
    self.add(G)
    self.add(G1)
    self.play(Write(Text('Zig-zag').next_to(G, UP)), Write(Text('Zig-zig').next_to(G1, UP)))
    self.splay(G, g, 4, -5)
    self.splay(G1, g1, 5, 1)
    # g = self.rotate(G, g, 2)
    # self.rotate(G, g, 2)
