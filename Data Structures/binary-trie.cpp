#include <bits/stdc++.h>
using namespace std;
using LL = long long;
void maximize(int &a, int b) {
    a = max(a, b);
}
// min for upper_bound, full for mex
namespace trie {
    const int N = 1e6 + 5, b = 30;
    int tc = 1;
    struct node{
        int vis = 0, cnt = 0, min = INT_MAX;
        int to[2] = {0, 0};
        bool full = 0;
        void update() {
            to[0] = to[1] = cnt = full = 0;
            vis = tc;
            min = INT_MAX;
        }
    } T[N + 2];
    node *root = T;
    int ptr = 0;
    node* nxt(node* cur, int x) {
        if(cur -> to[x] == 0) cur -> to[x] = ++ptr;
        assert(ptr < N);
        int idx = cur -> to[x];
        if(T[idx]. vis < tc) T[idx].update();
        return T + idx;
    }
    void insert(int val, node* cur = root, int k = b - 1) {
        cur -> cnt++;
        if(k < 0) {
            cur -> min = val;
            cur -> full = 1; 
        } else {
            insert(val, nxt(cur, val >> k & 1), k - 1);
            cur -> full = nxt(cur, 0) -> full and nxt(cur, 1) -> full;
            cur -> min = min(nxt(cur, 0) -> min, nxt(cur, 1) -> min);
        }
    }
    int mex(node* cur = root, int k = b - 1) {
        if(k < 0) return 0;
        if(nxt(cur, 0) -> full) return (1 << k) | mex(nxt(cur, 1), k - 1);
        return mex(nxt(cur, 0), k - 1);
    }
    int upper_bound(int val) {
        int ans = INT_MAX;
        node* cur = root;
        for(int k = b - 1; ~k; k--) {
            if(!(val >> k & 1)) {
                ans = min(ans, nxt(cur, 1) -> min);
            }
            cur = nxt(cur, (val >> k & 1));
        }
        // ans = min(ans, cur -> min); // this is lower_bound
        return ans;
    }
    void clear() {
        tc++;
        ptr = 0;
        root -> update();
    }
}
int main() {
    ios_base ::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    while(n--) {
        int t, x;
        cin >> t >> x;
        if(t) cout << trie :: upper_bound(x) << '\n';
        else trie :: insert(x);
    }
}
