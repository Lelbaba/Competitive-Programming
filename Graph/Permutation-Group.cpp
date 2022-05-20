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
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <typename DT> 
using ordered_set = tree <DT, null_type, less<DT>, rb_tree_tag,tree_order_statistics_node_update>;

class Permutation {
public:
    int n;
    bool parity;
    vector <int> a;
    vector < vector <int>> cyc;
    Permutation(int n = 0): n(n), a(n) {
        iota(a.begin(), a.end(), 0);
    }
    Permutation(const vector <int> &a) : n(a.size()), a(a) {}
    int& operator [] (int idx){
        return a[idx];
    }
    // permutation multiplication is associative and anti-commutative
    Permutation operator * (const Permutation &p){
        Permutation ans(n);
        for(int i = 0; i < n; i++) {
            ans[i] = a[p.a[i]];
        }
        return ans;
    }
    Permutation operator !() {
        Permutation ans(n);
        for(int i = 0; i < n; i++) {
            ans[a[i]] = i;
        }
        return ans;
    }
    vector <vector <int>>& CyclicDecomposition(){
        vector <bool> vis(n);
        vector <int> st;
        for(int i = 0; i < n; i++) if(!vis[i]) {
            st.push_back(i);
            while(a[st.back()] != i){
                st.push_back(a[st.back()]);
                vis[st.back()] = true;
            }
            cyc.push_back(st);
            st.clear();
            parity ^= cyc.size() - 1 & 1;
        }
        return cyc;
    }
    void Scan(int shift = 0){
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i]-= shift;
        }
    }
    LL Inversion() {
        LL ans = 1LL * n * (n - 1) / 2;
        ordered_set <int> s;
        for(int i = 0; i < n; i++){
            ans -= s.order_of_key(a[i]);
            s.insert(a[i]);
        }
        return ans;
    }
};
/*....................................................................*/ 

int main()
{
    monke_flip
    Permutation A({1, 2, 0, 5, 3, 6, 4}), B({6, 2, 3, 0, 5, 4, 1});
    dbg((B * A * A * B).a);
    return MONKE;
}