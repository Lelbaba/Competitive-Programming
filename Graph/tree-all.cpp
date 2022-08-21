#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
const int MONKE = 0;
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

class tree {
    int time = 0;
    vector <vector <int> > adj;
public:
    int n;
    inline vector<int>& operator[](int u) {
        return adj[u];
    }
    tree(int n = 0) : n(n), adj(n) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};
struct lca_table {
    tree &T;
    int n, LOG = 20;
    vector <vector <int>> anc;
    vector <int> level;

    void setupLifting(int node, int par) {
        for (int v : T[node]) if (v != par){
            anc[v][0] = node, level[v] = level[node] + 1;
            for (int k = 1; k < LOG; k++)
                anc[v][k] = anc[anc[v][k - 1]][k - 1];
            setupLifting(v, node);
        }
    }
    lca_table(tree &T, int root = 0): T(T), n(T.n) {
        LOG = 33 - __builtin_clz(n);
        anc.assign(n, vector <int> (LOG, root));
        level.resize(n);
        setupLifting(root, root);
    }
    int lca(int u, int v) {
        if (level[u] > level[v])
            swap(u, v);
        for (int k = LOG - 1; ~k; k--)
            if (level[u] + (1 << k) <= level[v])
                v = anc[v][k];
        if (u == v)
            return u;
        for (int k = LOG - 1; ~k; k--)
            if (anc[u][k] != anc[v][k])
                u = anc[u][k], v = anc[v][k];
        return anc[u][0];
    }
    int getAncestor(int node, int ht) {
        for (int k = 0; k < LOG; k++)
            if (ht & (1 << k))
                node = anc[node][k];
        return node;
    }
    int distance(int u, int v) {
        int g = lca(u, v);
        return level[u] + level[v] - 2 * level[g];
    }
};
struct euler_tour {
    int time = 0;
    tree &T;
    int n;
    vector <int> start, finish, level, par;
    euler_tour(tree &T, int root = 0) : T(T), n(T.n), start(n), finish(n), level(n), par(n) {
        time = 0;
        call(root);
    }
    void call(int node, int p = -1) {
        if (p != -1) level[node] = level[p] + 1;
        start[node] = time++;
        for (int e : T[node]) if (e != p)
            call(e, node);
        par[node] = p;
        finish[node] = time++;
    }
    bool isAncestor(int node, int par) {
        return start[par] <= start[node] and finish[par] >= finish[node];
    }
    int subtreeSize(int node) {
        return finish[node] - start[node] + 1 >> 1;
    }
};
tree virtual_tree(vector <int> &nodes, lca_table &table, euler_tour &tour) {
    sort(nodes.begin(), nodes.end(), [&](int x, int y) {
        return tour.start[x] < tour.start[y];
    });
    int n = nodes.size();
    for(int i = 0; i + 1 < n; i++) 
        nodes.push_back(table.lca(nodes[i], nodes[i + 1]));
    sort(nodes.begin(), nodes.end());
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
    sort(nodes.begin(), nodes.end(), [&](int x, int y) {
        return tour.start[x] < tour.start[y];
    });
    n = nodes.size();
    stack <int> st;
    st.push(0);
    tree ans(n);
    for(int i = 1; i < n; i++) {
        while(!tour.isAncestor(nodes[i], nodes[st.top()])) st.pop();
        ans.addEdge(st.top(), i);
        st.push(i);
    }
    return ans;
}
bool check(tree &T) {
    for(int i = 0; i < T.n; i++)
        if(T[i].size() > 2) return false;
    return true;
}

// USACO yinyangpath
// template <typename DT> class c_vector : public vector <DT> {
// public:
//     using vector <DT> :: vector;  
//     using vector <DT> :: begin;
//     using vector <DT> :: size;
//     DT& operator [] (int _idx) {
//         _idx = _idx % int(size());
//         size_t idx = _idx + size() * (_idx < 0);
//         return idx >= 0 and idx < size() ? *(begin() + idx) : *(begin() + (size() + idx));
//     }
//     void clear(int l, int r){
//         for(int i = l; i <= r; i++)
//             (*this)[i] = 0;
//     }
// };
// class Centroid_Decomposition {
//     vector <bool> blocked;
//     vector <int> CompSize;
//     int CompDFS(Tree &T, int node, int par) {
//         CompSize[node] = 1;
//         for(int &e: T[node]) if(e != par and !blocked[e])
//             CompSize[node] += CompDFS(T, e, node);
//         return CompSize[node];
//     }
//     int FindCentroid(Tree &T, int node, int par, int sz) {
//         for(int &e: T[node]) if(e != par and !blocked[e]) if(CompSize[e] > sz / 2)
//             return FindCentroid(T, e, node, sz);
//         return node;
//     }
//     pair <int,int> GetCentroid(Tree &T, int entry) {
//         int sz = CompDFS(T, entry, entry);
//         return {FindCentroid(T, entry, entry, sz), sz};
//     }
//     c_vector <LL> left[2], right[2]; 
//     int GMin, GMax;
//     void dfs(Tree &T, int node, int par, int Min, int Max, int sum) {
//         if(blocked[node])
//             return;
//         right[Max < sum or Min > sum][sum]++;
//         Max = max(Max, sum), Min = min(Min, sum);
//         GMin = min(GMin, sum), GMax = max(GMax, sum);
//         for(size_t i = 0; i < T[node].size(); i++) if(T[node][i] != par) {
//             dfs(T, T[node][i], node, Min, Max, sum + T.col[node][i]);
//         }
//     }
//     LL solve(Tree &T, int c, int sz) {
//         LL ans = 0;
//         left[0].clear(-sz, sz), left[1].clear(-sz, sz);
//         for(size_t i = 0; i < T[c].size(); i++) {
//             GMin = 1, GMax = -1;
//             dfs(T, T[c][i], c, GMin, GMax, T.col[c][i]);
//             ans += right[0][0] + left[1][0] * right[1][0];
//             for(int j:{0, 1} ) for(int k = GMin; k <= GMax; k++) {
//                 ans += right[j][k] * (left[0][-k] + (j == 0) * left[1][-k]);
//             }
//             for(int j:{0, 1} ) for(int k = GMin; k <= GMax; k++)  {
//                 left[j][k] += right[j][k];
//                 right[j][k] = 0;
//             }
//         }
//         return ans;
//     }
// public:
//     LL operator () (Tree &T, int entry) {
//         blocked.resize(T.n);
//         CompSize.resize(T.n);
//         for(int i:{0, 1})
//             left[i].resize(2 * T.n + 5), right[i].resize(2 * T.n + 5);
//         auto[c, sz] = GetCentroid(T, entry);
//         LL ans = solve(T, c, sz);
//         blocked[c] = true;
//         for(int e: T[c]) if(!blocked[e])
//             ans += (*this)(T, e);
//         return ans;
//     }   
// };
int main()
{
    monke_flip
    //freopen("yinyang.in", "r", stdin);
    //freopen("yinyang.out", "w", stdout);
    int n;
    cin >> n;
    // Tree T(n);
    // Centroid_Decomposition Decomposer;
    // for(int i = 0, u, v, cl; i < n - 1; i++) {
    //     cin >> u >> v >> cl;
    //     T.AddEdge(u - 1, v - 1, 2 * cl - 1);
    // }
    // cout << Decomposer(T, 0);
    return MONKE;
}