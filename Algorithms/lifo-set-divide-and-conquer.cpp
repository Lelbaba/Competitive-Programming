#include<bits/stdc++.h>
using namespace std;
using LL = long long;
/*
 * https://judge.yosupo.jp/submission/125304
 * https://codeforces.com/blog/entry/104443
 *
 * Dynamic Connectivity Offline by Divide and Conquer
 * DSU with Rollback used as the LIFO-set
 */
const int N = 6e5 + 5, B = 450;
LL a[N];
vector <pair <int, int>> dbg;
int L, R;
namespace dsu {
    int par[N], sz[N];
    vector <pair <int, int>> op;
    void init(int n) {
        iota(par, par + n, 0);
        fill(sz, sz + n, 1);
        op.clear();
    }
    int root(int u) {
        while(u != par[u]) u = par[u];
        return u;
    }
    void merge(int u, int v) {
        if(sz[u = root(u)] < sz[v = root(v)]) swap(u, v);
        if(u == v) return;
        op.emplace_back(u, v);
        sz[u] += sz[v];
        a[u] += a[v];
        par[v] = u;
    }
    void undo() {
        int u, v; tie(u, v) = op.back();
        op.pop_back();
        sz[u] -= sz[v];
        a[u] -= a[v];
        par[v] = v;
    }
    void rollback(int t) {
        while(t < op.size()) {
            undo();
        }
    }
}
namespace up {
    int l[N], r[N], u[N], v[N], tm;
    void push(int _l, int _r, int _u, int _v) {
        l[tm] = _l, r[tm] = _r, u[tm] = _u, v[tm] = _v;
        tm++;
    }
}
namespace que {
    int node[N], tm;
    LL ans[N];
    void push(int _node){
        node[++tm] = _node;
    } 
}
namespace edge_set {
    void push(int i) {
        dsu :: merge(up :: u[i], up :: v[i]);
    }
    void pop(int t) {
        dsu :: rollback(t);
    }
    int time() {
        return dsu :: op.size();
    }
    LL query(int u) {
        return a[dsu :: root(u)];
    }
}
namespace dncq {
    vector <int> tree[4 * N];
    void update(int idx, int l = 0, int r = que :: tm, int node = 1) {
        int ul = up :: l[idx], ur = up :: r[idx];
        if(r < ul or ur < l) return;
        if(ul <= l and r <= ur) {
            tree[node].push_back(idx);
            return;
        }
        int m = l + r >> 1;
        update(idx, l, m, node << 1);
        update(idx, m + 1, r, node << 1 | 1);
    }
    void dfs(int l = 0, int r = que :: tm, int node = 1) {
        int cur = edge_set :: time();
        for(int e: tree[node]) edge_set :: push(e);
        if(l == r) {
            que :: ans[l] = edge_set :: query(que :: node[l]);
        } else {
            int m = l + r >> 1;
            dfs(l, m, node << 1);
            dfs(m + 1, r, node << 1 | 1);
        }
        edge_set :: pop(cur);
    }
}
void push_updates() {
    for(int i = 0; i < up :: tm; i++) dncq :: update(i);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++) 
        cin >> a[i];
    map <pair <int, int>, int> last; 
    while(q--) {
        pair <int, int> edg;
        int &u = edg.first, &v = edg.second, tp, &cur = que :: tm;
        cin >> tp; 
        if(tp < 2) {
            cin >> u >> v;
            if(u > v) swap(u, v);
            if(tp) {
                int l = last[edg] + 1, r = cur;
                up :: push(l, r, u, v);
                last.erase(edg);
            } else last[edg] = cur;
        } else if(tp == 2) {
            cin >> u >> a[v = n++];
            last[edg] = cur;
        } else {
            cin >> u;
            que :: push(u);
        }
    }
    int r = que :: tm;
    for(auto &e: last) {
        int l = e.second + 1, u = e.first.first, v = e.first.second;
        up :: push(l, r, u, v);
    }
    dsu :: init(n + 1);
    push_updates();
    dncq :: dfs();
    for(int i = 1; i <= que :: tm; i++) cout << que :: ans[i] << '\n';
}
