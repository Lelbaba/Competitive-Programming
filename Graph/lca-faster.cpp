#include <bits/stdc++.h>
using namespace std;
using LL = long long;

/*....................................................................*/ 

/*....................................................................*/ 
const int N = 5e5 + 5, B = 20;
using Tree = vector <vector <int>>;

namespace lca1 {
    int st[N], lvl[N];
    int tbl[B][2 * N];
    int t = 0;

    void dfs(int u, int p, Tree &T) {
        st[u] = t;
        tbl[0][t++] = u;
        for(int v: T[u]) {
            if(v == p) continue;
            lvl[v] = lvl[u] + 1;
            dfs(v, u, T);
            tbl[0][t++] = u;
        }
    }
    int low(int u, int v) {
        return make_pair(lvl[u], u) < make_pair(lvl[v], v) ? u : v;
    }

    void makeTable(int n) {
        int m = 2 * n - 1;
        for(int b = 1; b < B; b++) {
            for(int i = 0; i < m; i++) {
                tbl[b][i] = low(tbl[b - 1][i], tbl[b - 1][i + (1 << b - 1)]);
            }
        }
    }

    int lca(int u, int v) {
        int l = st[u], r = st[v];
        if(l > r) swap(l, r);
        int k = __lg(r - l + 1);
        return low(tbl[k][l], tbl[k][r - (1 << k) + 1]);
    }
    void init(int root, Tree &T) {
        lvl[root] = 0;
        t = 0;
        dfs(root, root, T);
        makeTable(T.size());
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    Tree T(n);
    for(int i = 1; i < n; i++) {
        int x;
        cin >> x;
        T[x].push_back(i);
    }
    lca1 :: init(0, T);

    while(q--) {
        int u, v;
        cin >> u >> v;
        cout << lca1 :: lca(u, v) << '\n';
    }
}
