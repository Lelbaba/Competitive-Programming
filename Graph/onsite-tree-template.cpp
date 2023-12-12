#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using LL = long long;

/*....................................................................*/ 

/*....................................................................*/ 

const int N = 3e5 + 5, B = 19;
LL ans = 0;

int val[N];
int bst[N][2];

using Tree = vector <vector <int>>;

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
    bool isAncestor(int u, int p) {
        return st[p] <= st[u] and en[u] <= en[p];
    }

    void tour(int u, int p, Tree &T) {
        st[u] = t++;
        int idx = 0;
        for(int v: T[u]) {
            if(v == p) continue; 
//            nxt[v] = (idx++ ? v : nxt[u]); // only for hld
            anc[0][v] = u, lvl[v] = lvl[u] + 1;
            tour(v, u, T);
        }
        en[u] = t; // [st, en] contains subtree range 
    }

//    void hld(int u, int p, Tree &T) {
//        sz[u] = 1;
//
//        int eld = 0, mx = 0, idx = 0;
//        for(int i = 0; i < T[u].size(); i++) {
//            int v = T[u][i];
//            if(v == p) continue;
//            hld(v, u, T);
//
//            if(sz[v] > mx) mx = sz[v], eld = i;
//            sz[u] += sz[v];
//        }
//        swap(T[u][0], T[u][eld]);
//    }
//
//    LL climbQuery(int u, int g) {
//        LL ans = -INF;
//        while(1) {
//            int _u = nxt[u];
//            if(isAncestor(g, _u)) _u = g;
//            ans = max(ans, rmq :: query(st[_u], st[u]));
//
//            if(_u == g) break;
//            u = anc[0][_u];
//        }
//        return ans;
//    }
//
//    LL pathQuery(int u, int v) {
//        int g = lca(u, v);
//        return max(climbQuery(u, g), climbQuery(v, g));
//    }

    void init(int u, Tree &T) {
        int n = T.size();
        anc[0][u] = nxt[u] = u;
        t = 0;
//        hld(u, u, T);
        tour(u, u, T);
        initLifting(n);
    }
}

namespace ct {
    int par[N], cnt[N], cntp[N];
    LL sum[N], sump[N];
    void activate(int u) {
        int v = u, _u = u;

        ans += sum[u];
        cnt[u]++;

        while(par[u] != -1) {
            u = par[u];
            LL d = ta :: dis(_u, u);
            ans += sum[u] - sump[v];
            ans += d * (cnt[u] - cntp[v]);

            sum[u] += d;
            cnt[u]++;

            sump[v] += d;
            cntp[v]++;

            v = u;
        }
    }
}



namespace ctrd {
    int sz[N];
    bool blk[N];

    int szCalc(Tree &T, int u, int p = -1) {
        sz[u] = 1;
        for(int v: T[u]) {
            if(v == p or blk[v]) continue;
            sz[u] += szCalc(T, v, u);
        }
        return sz[u];
    }
    int getCentroid(Tree &T, int u, int s, int p = -1) {
        for(int v: T[u]) {
            if(v == p or blk[v]) continue;
            if(sz[v] * 2 >= s) return getCentroid(T, v, s, u);
        }
        return u;
    }

    void decompose(Tree &T, int u, int p = -1) {
        szCalc(T, u);
        u = getCentroid(T, u, sz[u]);
        ct :: par[u] = p;

        blk[u] = 1;
        for(int v: T[u]) {
            if(!blk[v]) decompose(T, v, u);
        }
    }
}

void addEdge(Tree &T, int u, int v) {
    T[u].push_back(v);
    T[v].push_back(u);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n;
    cin >> n;

    vector <int> a(n);
    set <int> s;

    Tree T(n + 1);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(i > 0) {
            auto it = s.upper_bound(a[i]);
            if(it == s.end() or bst[*it][0]) it--;
            bst[*it][*it < a[i]] = a[i];
            addEdge(T, *it, a[i]);
        }
        s.insert(a[i]);
    }

    ta :: init(a[0], T);

    ctrd :: decompose(T, 1);

    for(int e: a) {
        ct :: activate(e);
        cout << ans << '\n';
    }
}
