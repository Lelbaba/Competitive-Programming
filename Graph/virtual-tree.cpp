
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using LL = long long;
using PII = pair <int, int>;

#ifdef LEL
#include "dbg.h"
#else
#define dbg(...) {/*temon kichu na*/}
#endif
/*.................................................................... 
 * Solves https://lightoj.com/problem/game-strategies
 * From ICPC 2023 Dhaka Regional
 * vt is the namespace for virtual tree
 * lca1 is the namespace for O(1) lca
....................................................................*/  
const int N = 1e6 + 5, B = 22;
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
namespace vt {
    int st[N], en[N], t;
    vector <int> adj[N];

    void dfs(int u, int p, Tree &T) {
        st[u] = t++;
        for(int v: T[u]) if(v != p) dfs(v, u, T);
        en[u] = t++;
    }
    bool comp(int u, int v) {
        return st[u] < st[v];
    }
    bool isAncestor(int u, int p) {
        return st[p] <= st[u] and en[u] <= en[p];
    }

    void construct(vector <int> &nodes) {
        sort(nodes.begin(), nodes.end(), comp);
        int n = nodes.size();
        for(int i = 0; i + 1 < n; i++) {
            nodes.push_back(lca1 :: lca(nodes[i], nodes[i + 1]));
        }
        sort(nodes.begin(), nodes.end(), comp);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        n = nodes.size();
        stack <int> s;
        s.push(nodes[0]);
        for(int i = 1; i < n; i++) {
            int u = nodes[i];
            while(not isAncestor(u, s.top())) s.pop();
            adj[s.top()].push_back(u);
            s.push(u);
        }
    }
    void clear(vector <int> &nodes) {
        for(int u: nodes) {
            adj[u].clear();
        }
    }

    void init(int root, Tree &T) {
        lca1 :: init(root, T);
        t = 0;
        dfs(root, root, T);
    }
}

int col[N];
Tree T;
const LL MOD = 1e9 + 7;

LL dfs(int u, int p, int c) {
    using vt :: adj;
    if(col[u] != c) {
        LL ans = 1;
        for(int v: adj[u]) {
            ans = (ans * dfs(v, u, c)) % MOD;
        }
        return ans;
    } else {
        LL ans = T[u].size() - adj[u].size();
        for(int v: adj[u]) {
            ans = (ans + dfs(v, u, c)) % MOD;
        }
        return ans;
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int cs;
    cin >> cs;
    for(int tc = 1; tc <= cs; tc++) {
        int n, k;
        cin >> n >> k;
        T.clear();
        T.resize(n + 1);
        
        for(int i = 1, p; i <= n; i++) {
            cin >> p;
            T[p].push_back(i);
        }

        vector <vector <int>> nodes(k + 1);

        for(int i = 1; i <= n; i++) {
            cin >> col[i];
            nodes[col[i]].push_back(i);
        }

        vt :: init(0, T);
        cout << "Case " << tc << ":";
        for(int i = 1; i <= k; i++) {
            nodes[i].push_back(0);
            vt :: construct(nodes[i]);
            cout << " " << dfs(0, 0, i);
            vt :: clear(nodes[i]);
        }
        cout << '\n';
    }
}
