#include <bits/stdc++.h>
using namespace std;
using LL = long long;

class Tree {
    int time = 0;
    vector<vector<int>> adj;
    vector<int> start, finish, level, par;

   public:
    int n;
    inline vector<int> &operator[](int u) { return adj[u]; }
    Tree(int n = 0) : n(n), adj(n) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};
struct euler_tour {
    int time = 0;
    int n;
    vector<int> start, finish, par;
    Tree &T;
    euler_tour(Tree &T, int root = 0)
        : T(T), n(T.n), start(n), finish(n), par(n) {
        time = 0;
        Call(root);
    }
    void Call(int node, int p = -1) {
        start[node] = time++;
        for (int e : T[node])
            if (e != p) Call(e, node);
        par[node] = p;
        finish[node] = time++;
    }
    bool isAncestor(int node, int par) {
        return start[par] <= start[node] and finish[par] >= finish[node];
    }
    int subtreeSize(int node) { return finish[node] - start[node] + 1 >> 1; }
};
struct lca_table {
    Tree &T;
    int n, LOG = 25;
    vector<vector<int>> anc;
    vector<int> level;

    void setupLifting(int node, int par) {
        for (int v : T[node]) {
            if (v == par) continue;
            anc[v][0] = node;
            level[v] = level[node] + 1;
            for (int k = 1; k < LOG; k++) anc[v][k] = anc[anc[v][k - 1]][k - 1];
            setupLifting(v, node);
        }
    }
    lca_table(Tree &T, int root = 0) : T(T), n(T.n) {
        LOG = 33 - __builtin_clz(n);
        anc.assign(n, vector<int>(LOG, root));
        level.resize(n);
        setupLifting(root, root);
    }
    int lca(int u, int v) {
        if (level[u] > level[v]) swap(u, v);
        for (int k = LOG - 1; k >= 0; k--)
            if (level[u] + (1 << k) <= level[v]) v = anc[v][k];
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; k--)
            if (anc[u][k] != anc[v][k]) u = anc[u][k], v = anc[v][k];
        return anc[u][0];
    }
    int getAncestor(int node, int ht) {
        for (int k = 0; k < LOG; k++)
            if (ht & (1 << k)) node = anc[node][k];
        return node;
    }
    int dis(int u, int v) { return level[u] + level[v] - 2 * level[lca(u, v)]; }
};

set<int> GetCenters(Tree &T) {
    int n = T.n;
    vector<int> deg(n), q;
    set<int> s;
    for (int i = 0; i < n; i++) {
        deg[i] = T[i].size();
        if (deg[i] == 1) q.push_back(i);
        s.insert(i);
    }
    while (s.size() > 2) {
        vector<int> t;
        for (auto x : q) {
            for (auto e : T[x]) {
                if (--deg[e] == 1) t.push_back(e);
            }
            s.erase(x);
        }
        q = t;
    }
    return s;
}
int main() {
    ios_base ::sync_with_stdio(0);
    cin.tie(0);
    return 0;
}
