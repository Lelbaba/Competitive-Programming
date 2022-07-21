#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke chrono::system_clock::now().time_since_epoch().count()
#ifdef LEL
#include "dbg.h"
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
using ULL = unsigned long long;
mt19937_64 rng(random_monke);
const int MONKE = 0;

/*....................................................................*/ 
int Log(int n) {
    return 31 - __builtin_clz(n);
}
template <typename T> struct sparse_table {
    vector <vector<T>> table;
    function < T(T, T) > &func;
    T id;

    sparse_table(const vector <T> &v, function <T(T, T)> func, T id) : func(func), id(id) {
        int sz = v.size();
        table.assign(sz, vector <T> (Log(sz) + 1) );

        for (int j = 0; j <= Log(sz); j++) {
            for (int i = 0; i + (1 << j) <= sz; i++) {
                if (j == 0) table[i][j] = func(v[i], id);    // base case, when only 1 element in range
                else table[i][j] = func(table[i][j - 1], 
                    table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    // when intersection of two ranges wont be a problem like min, gcd,max
    T query(int l, int r) {
        assert(r >= l);
        int pow = Log(r - l + 1);
        return func(table[l][pow], table[r - (1 << pow) + 1][pow]);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector <LL> arr(n + 1);
    for (int i = 0; i < n; i++) {
        if (s[i] == '+') arr[i + 1] = arr[i] + 1;
        else arr[i + 1] = arr[i] - 1;
    }
    sparse_table <LL> MIN(arr, [](LL a, LL b) {return min(a, b);}, LLONG_MAX);
    sparse_table <LL> MAX(arr, [](LL a, LL b) {return max(a, b);}, LLONG_MIN);
    while (m--) {
        int l, r;
        cin >> l >> r;
        LL mn = MIN.query(0, l - 1);
        LL mx = MAX.query(0, l - 1);
        if (n > r) {
            mn = min(mn, arr[l - 1] - arr[r] + MIN.query(r + 1, n));
            mx = max(mx, arr[l - 1] - arr[r] + MAX.query(r + 1, n));
        }
        cout << mx - mn + 1 << '\n';
    }
}
/*....................................................................*/ 
bool calc(LL ay, LL k, LL m, LL M) {
    LL lo = 0, hi = m, ans = -1;
    while(lo <= hi) {
        LL mid =  lo + hi >> 1;
        if(ay + mid * k > M) ans = mid, hi = mid - 1;
        else lo = mid + 1;
    }
    if(ans == -1) return false;
    if(ay + k * ans > m) return false;
    return true;
}
int main()
{
    monke_flip
    int n, m;
    cin >> n >> m;
    vector <LL> block(m + 1);
    for(int i = 1; i <= m; i++)
        cin >> block[i];
    sparse_table <LL> T(block, [](LL a, LL b) { return max(a, b);}, 0);
    int q;
    cin >> q;
    while(q--){
        int ax, ay, bx, by, k;
        cin >> ax >> ay >> bx >> by >> k;
        if((ax - bx) % k != 0 or (ay - by) % k != 0){
            cout << "NO\n";
            continue;
        }
        if(ax <= block[ay] or bx <= block[by]) {
            cout << "NO\n";
            continue;
        }
        if(ay > by) swap(ay, by);
        LL M = T.query(ay, by);
        if(calc(ax, k, n, M)) cout << "YES\n";
        else cout << "NO\n";
    }
    return MONKE;
}