#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke chrono::system_clock::now().time_since_epoch().count()
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
using ULL = unsigned long long;
mt19937_64 rng(random_monke);
const int MONKE = 0;

/*....................................................................*/
const int N = 200005;

map <string, int> id;
string query[N], s, comp[N];
int n, m, ptr, last[N], ans[N];
int ending[N];
int counter[N], starting[N];
struct AC {
    int N, P;
    vector<vector<int>> next;
    vector<int> link, out_link;
    vector<vector<int>> out;
    AC(): N(0), P(0) { node(); }
    int node() {
        next.emplace_back(26, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return N++;
    }
    int add_pattern(const string T) {
        int u = 0;
        for (auto c : T) {
            if (!next[u][c - 'a']) next[u][c - 'a'] = node();
            u = next[u][c - 'a'];
        }
        out[u].push_back(P);
        return P++;
    }
    void compute() {
        queue<int> q;
        for (q.push(0); !q.empty(); ) {
            int u = q.front(); q.pop();
            // automaton:
            for (int c = 0; c < 26; ++c) {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c];
                else {
                    link[v] = u ? next[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }
    int advance(int u, char c) {
        while (u && !next[u][c - 'a']) u = link[u];
        u = next[u][c - 'a'];
        return u;
    }
    void match(const string S) {
        int u = 0;
        for (int i = 0; i < S.size(); ++i) {
            char c = S[i];
            u = advance(u, c);

            for (int v = u; v; v = out_link[v]) {
                for (auto p : out[v]) {
                    ++ans[p];
                    ending[i] += counter[p];
                    starting[i - comp[p].size() + 1] += counter[p];
                    last[p] = i;
                }
            }
        }
    }
} aho;


/*....................................................................*/

int main()
{
    monke_flip

    return MONKE;
}