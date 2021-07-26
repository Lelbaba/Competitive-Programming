#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using ll = long long;
const int MONKE = 0;

class BIT {
    public:
        vector<int> tree; 
        int n;

    BIT(int n) {
        this->n = n;
        tree.assign(n, 0);
    }

    BIT(vector<int> a) : BIT(a.size()) {
        for (int i = 0; i < a.size(); i++){
            add(i, a[i]);
        }
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1){
            ret += tree[r];
        }
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1)){
            tree[idx] += delta;
        }
    }
};
int main()
{
    monke_flip
    
    return MONKE;
}