#include <bits/stdc++.h>
using namespace std;
using LL = long long;

// solves https://dmoj.ca/problem/coci07c4p5
const int N = 1e6 + 2;
using PLL = pair<int, int>;

constexpr PLL id = {1, -1};
namespace segtree {
    PLL tree[2 * N + 5];
    PLL combine(PLL l, PLL r) { return max(l, r); }
    void update(int p, PLL v) {
        p--;
        for (tree[p += N] = v; p >>= 1;) tree[p] = combine(tree[p << 1], tree[p << 1 | 1]);
    }
    PLL query(int l, int r) {
        PLL resl = id, resr = id;
        --l;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = combine(resl, tree[l++]);
            if (r & 1) resr = combine(tree[--r], resr);
        }
        return combine(resl, resr);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<PLL> ranges(n);
    for (auto &e : ranges) {
        cin >> e.first >> e.second;
        e.first *= -1;
    }
    fill(segtree :: tree, segtree :: tree + 2 * N, make_pair(1, -1));
    sort(ranges.begin(), ranges.end());
    vector<int> path(n, -1);
    int mx = 0, idx = 0;
    for (int i = 0; i < n; i++) {
        auto ans = segtree :: query(-ranges[i].first, ranges[i].second);
        if (ans.first + 1 > mx) mx = ans.first + 1, idx = i;
        path[i] = ans.second;
        segtree :: update(ranges[i].second, {ans.first + 1, i});
    }
    vector<int> ans;
    while (idx != -1) {
        ans.push_back(idx);
        idx = path[idx];
    }
    cout << ans.size() << '\n';
    for (auto e : ans)
        cout << -ranges[e].first << ' ' << ranges[e].second << '\n';
}
