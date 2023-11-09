#include <bits/stdc++.h>
using namespace std;
using LL = long long;

/*
 * Solves GYM 103446H
 */

const int N = 2e5 + 5, B = 19;
const LL INF = 1e18;

using vec = vector <int>;
using mat = vector <vec>;
using Tree = mat;

void addEdge(Tree &T, int u, int v) {
    T[u].push_back(v);
    T[v].push_back(u);
}

namespace rmq {
    LL tbl[B][N], a[N];

    void init(int n) {
        for(int i = 0; i < n; i++) tbl[0][i] = a[i];
        for(int b = 1; b < B; b++) {
            for(int i = 0; i < n; i++) {
                tbl[b][i] = max(tbl[b - 1][i], tbl[b - 1][i + (1 << (b - 1))]);
            }
        }
    }

    LL query(int l, int r) {
        if(r < l) return -INF;
        int b = __lg(r - l + 1);
        return max(tbl[b][l], tbl[b][r - (1 << b) + 1]);
    }
}

namespace ta {
    int anc[B][N], sz[N], lvl[N], st[N], en[N], nxt[N], t = 0;

    void initLifting(int n) {
        for(int b = 1; b < B; b++) {
            for(int i = 0; i < n; i++) {
                anc[b][i] = anc[b - 1][anc[b - 1][i]];
            }
        }
    }

    int kthAncestor(int u, int k) {
        for(int b = 0; b < B; b++) {
            if(k >> b & 1) u = anc[b][u];
        }
        return u;
    }

    int lca(int u, int v) {
        if(lvl[u] > lvl[v]) swap(u, v);
        v = kthAncestor(v, lvl[v] - lvl[u]);

        if(u == v) return u;

        for(int b = B - 1; b >= 0; b--) {
            if(anc[b][u] != anc[b][v]) u = anc[b][u], v = anc[b][v];
        }
        return anc[0][u];
    }

    int dis(int u, int v) {
        int g = lca(u, v);
        return lvl[u] + lvl[v] - 2 * lvl[g];
    }
    bool isAncestor(int u, int v) {
        return st[v] <= st[u] and en[u] <= en[v];
    }

    void tour(int u, int p, Tree &T) {
        st[u] = t++;
        int idx = 0;
        for(int v: T[u]) {
            if(v == p) continue; 
            nxt[v] = (idx++ ? v : nxt[u]); // only for hld
            anc[0][v] = u, lvl[v] = lvl[u] + 1;
            tour(v, u, T);
        }
        en[u] = t; // [st, en] contains subtree range 
    }

    void hld(int u, int p, Tree &T) {
        sz[u] = 1;

        int eld = 0, mx = 0, idx = 0;
        for(int i = 0; i < T[u].size(); i++) {
            int v = T[u][i];
            if(v == p) continue;
            hld(v, u, T);

            if(sz[v] > mx) mx = sz[v], eld = i;
            sz[u] += sz[v];
        }
        swap(T[u][0], T[u][eld]);
    }

    LL climbQuery(int u, int g) {
        LL ans = -INF;
        while(1) {
            int _u = nxt[u];
            if(isAncestor(g, _u)) _u = g;
            ans = max(ans, rmq :: query(st[_u], st[u]));

            if(_u == g) break;
            u = anc[0][_u];
        }
        return ans;
    }

    LL pathQuery(int u, int v) {
        int g = lca(u, v);
        return max(climbQuery(u, g), climbQuery(v, g));
    }

    void init(int u, Tree &T) {
        int n = T.size();
        anc[0][u] = nxt[u] = u;
        lvl[u] = 0;
        hld(u, u, T);
        tour(u, u, T);
        initLifting(n);
    }
}

struct dsu {
    int n;
    vec par;
    vector <LL> pts;
    dsu(int _n) : n(_n), par(_n), pts(_n) {
        iota(par.begin(), par.end(), 0);
    }
    int root(int u) {
        if(u == par[u]) return u;
        return par[u] = root(par[u]);
    }
    int same(int u, int v) {
        return root(u) == root(v);
    }
    void unite(int u, int v) {
        u = root(u), v = root(v);
        if(u == v) return;
        par[v] = u;
        pts[u] += pts[v];
    }
};

void removeEdges(int n, int& m, vector <tuple <LL, int, int>> &edges) {
    vector <tuple <LL, int, int>> baki;
    sort(edges.begin(), edges.end());

    dsu G(n + 1);

    for(auto [w, u, v]: edges) {
        if(G.same(u, v)) continue;
        G.unite(u, v);
        baki.emplace_back(w, u, v);
    }
    edges = baki;
    m = baki.size();
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m, q;
    cin >> n >> m >> q;

    vector <LL> a(n + 1);

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }


    vector <tuple <LL, int, int>> edges(m);
    for(auto &[w, u, v]: edges) {
        cin >> u >> v >> w;
    }

    removeEdges(n, m, edges);

    vector <LL> val(n + m + 1);
    dsu G(n + m + 1);
    Tree T(n + m + 1);

    for(int i = 1; i <= n; i++) G.pts[i] = a[i];

    int _u = n, root = 1;
    for(auto [w, u, v]: edges) {
        _u++;
        if(G.same(u, v)) continue;
        u = G.root(u);
        v = G.root(v);

        addEdge(T, _u, u);
        addEdge(T, _u, v);

        val[u] = w - G.pts[u];
        val[v] = w - G.pts[v];

        G.unite(_u, u);
        G.unite(_u, v);
        root = _u;
    }

    ta :: init(root, T);
    for(int i = 1; i <= n + m; i++) {
        int j = ta :: st[i];
        rmq :: a[j] = val[i]; 
    }
    rmq :: init(n + m + 1);

    while(q--) {
        int u;
        LL w;
        cin >> u >> w;

        if(w < ta :: pathQuery(u, u)) {
            cout << w + G.pts[u] << '\n';
            continue;
        }

        int v = u;
        for(int b = B - 1; b >= 0; b--) {
            int _u = ta :: anc[b][v];
            if(ta :: pathQuery(u, _u) <= w) v = _u;
        }
        v = ta :: anc[0][v];
        cout << G.pts[v] + w << '\n'; 
    }
}
