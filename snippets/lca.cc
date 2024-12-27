// sparse table
const int K = 20;
int n, t = 0, tin[N], et[2 * N], c[N], d[N], st[2 * N][K]{};
int mind(int i, int j) { // min by depth
    return d[i] < d[j] ? i : j;
}
void build() {
	for (int i = 0; i < 2 * N; i++) st[i][0] = et[i];
	for (int k = 1; k < K; k++) for (int i = 0; i < 2 * N; i++) {
		st[i][k] = st[i][k - 1];
		if (int j = i + (1 << (k - 1)); j < 2 * N) st[i][k] = mind(st[i][k], st[j][k - 1]);
	}
}
int lca(int u, int v) { // lca of u and v
    u = tin[u], v = tin[v];
    if (u > v) swap(u, v);
    int k = lg(++v - u);
    return mind(st[u][k], st[v - (1 << k)][k]);
}

int dist(int u, int v) {
    return d[u] + d[v] - 2 * d[lca(u, v)];
}
