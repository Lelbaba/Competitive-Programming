// https://codeforces.com/contest/613/submission/236850843

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
/*....................................................................*/ 

/*....................................................................*/  
const int N = 5e5 + 5, B = 20;
using Tree = vector <vector <int>>;

namespace lca1 {
    int st[N], lvl[N];
    int tbl[B][2 * N];
    int tt = 0;

    void dfs(int u, int p, Tree &T) {
        st[u] = tt;
        tbl[0][tt++] = u;
        for(int v: T[u]) {
            if(v == p) continue;
            lvl[v] = lvl[u] + 1;
            dfs(v, u, T);
            tbl[0][tt++] = u;
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
        dfs(root, root, T);
        makeTable(T.size());
    }
}
namespace vt {
    int st[N], en[N], time = 0;
    bool mark[N];
    vector <int> adj[N];

    void dfs(int u, int p, Tree &T) {
        st[u] = time++;
        for(int v: T[u]) if(v != p) dfs(v, u, T);
        en[u] = time++;
    }
    bool comp(int u, int v) {
        return st[u] < st[v];
    }
    bool isAncestor(int u, int p) {
        return st[p] <= st[u] and en[u] <= en[p];
    }

    void construct(vector <int> &nodes) {
        for(int u: nodes) mark[u] = 1;
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
            adj[u].push_back(s.top());
            adj[s.top()].push_back(u);
            s.push(u);
        }
    }
    void clear(vector <int> &nodes) {
        for(int u: nodes) {
            mark[u] = 0;
            adj[u].clear();
        }
    }
    bool check(int u, int p) {
        using lca1 :: lvl;
        for(int v: adj[u]) if(v != p) {
            if(mark[u] and mark[v] and lvl[u] + 1 == lvl[v]) return false;
            if(not check(v, u)) return false;
        }
        return true;
    }
    pair <bool, int> solve(int u, int p) {
        int cur = 0, ans = 0;
        for(int v: adj[u]) if(v != p) {
            auto [cnt, tot] = solve(v, u);
            ans += tot;
            ans += (mark[u] and cnt);
            cur += cnt;
        }
        if(mark[u] or cur == 1) return make_pair(1, ans);
        ans += (cur > 1);
        return make_pair(0, ans);
    }

    void process(vector <int> &nodes) {
        construct(nodes);
        // problem specific solution here 
        /* -------------------------------------*/
        int u = nodes[0];
        if(not check(u, u)) cout << -1 << '\n';
        else cout << solve(u, u).second << '\n';
        /* -------------------------------------*/
        clear(nodes);
    }
    void init(int root, Tree &T) {
        lca1 :: init(root, T);
        dfs(root, root, T);
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n;
    cin >> n;
    Tree T(n + 1);
    for(int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        T[u].push_back(v);
        T[v].push_back(u);
    }
    vt :: init(1, T);
    int q;
    cin >> q;
    while(q--) {
        int k;
        cin >> k;
        vector <int> nodes(k);
        for(int &u: nodes) cin >> u;
        vt :: process(nodes);
    }
}
