#include<bits/stdc++.h>
using namespace std;
using LL = long long;
/*
 * CodeChef GERALD07
 * DSU with rollback should not have path compression 
 * Rollback can be done only one way, but MO moves the ranges around from both ends.
 * So the queries are processed block by block. For queries starting in the same block, 2 cases
 *
 * Case 1: ends in the same block: this should be bruteforced.
 * Case 2: ends in different block: 
 *      Sort the queries by incresing order of right-bound
 *      You don't have to rollback the right pointer while processing queries of this block 
 *      If you start adding from the end of the block to the left, you can always rollback 
 *      the left block and adjust for the range. 
 *      After processing all the left bound, end. 
 */
const int N = 2e5 + 5, B = 450;
int u[N], v[N], ans[N];
namespace dsu {
    int par[N], sz[N], comp;
    vector <pair <int, int>> op;
    void init(int n) {
        iota(par, par + n, 0);
        fill(sz, sz + n, 1);
        op.clear();
        comp = n;
    }
    int root(int u) {
        // no path compression
        while(u != par[u]) u = par[u];
        return u;
    }
    void merge(int u, int v) {
        if(sz[u = root(u)] < sz[v = root(v)]) swap(u, v);
        if(u == v) return;
        comp--;
        sz[u] += sz[v];
        par[v] = u;
        op.emplace_back(u, v);
    }
    void rollback(int t) {
        while(t < op.size()) {
            int u, v; tie(u, v) = op.back();
            sz[u] -= sz[v];
            par[v] = v;
            op.pop_back();
            comp++;
        }
    }
}
namespace mo {
    struct query {
        int l, r, id;
        query(int l, int r, int id) : l(l), r(r), id(id) {}
        bool operator < (const query &rhs) const {
            return make_tuple(l / B, r, l) < make_tuple(rhs.l / B, rhs.r, rhs.l); 
        }
    };
    vector <query> queries[B];
    int l, r;
    void add(int id) {
        dsu :: merge(u[id], v[id]);
    }
    void process_query(query &q) {
        for(int i = q.l; i <= q.r; i++) add(i);
        ans[q.id] = dsu :: comp - 1; 
        dsu :: rollback(0);
    }
    void process_block(int id) {
        sort(queries[id].begin(), queries[id].end());
        l = (id + 1) * B, r = l - 1;
        for(auto q: queries[id]) {
            while(r < q.r) add(++r);
            int cur = dsu :: op.size();
            while(l > q.l) add(--l);
            ans[q.id] = dsu :: comp - 1;
            dsu :: rollback(cur);
            l = (id + 1) * B;
        }
        dsu :: rollback(0);
    }
    void clear() {
        for(int i = 0; i < B; i++) queries[i].clear();
    }
    void scan_query(int id) {
        int l, r;
        cin >> l >> r;
        query q(l, r, id);
        if(l / B == r/ B) process_query(q);
        else queries[l / B].push_back(q); 
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        int n, m, q;
        cin >> n >> m >> q;
        dsu :: init(n + 1);
        for(int i = 1; i <= m; i++) cin >> u[i] >> v[i];
        for(int i = 1; i <= q; i++) mo :: scan_query(i);
        for(int i = 0; i <= m / B; i++) mo :: process_block(i);
        for(int i = 1; i <= q; i++) cout << ans[i] << '\n';
        mo :: clear();
    }
}
