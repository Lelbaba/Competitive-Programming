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

template <typename DT> class BIT {
    public:
        vector <DT> tree; 
        int n;
    BIT(int n) {
        this->n = n;
        tree.assign(n, 0);
    }
    BIT(const vector <DT> &a) : BIT(a.size()) {
        for (int i = 0; i < n; i++)
            add(i, a[i]);
    }
    DT sum(int r) {
        DT ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += tree[r];
        return ret;
    }
    DT sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    void add(int idx, DT delta) {
        for (; idx < n; idx = idx | (idx + 1))
            tree[idx] += delta;
    }
};
int main()
{
    monke_flip
    BIT <LL> T(5);
    return MONKE;
}