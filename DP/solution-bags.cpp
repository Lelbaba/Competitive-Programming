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

/*....................................................................*/ 
// find smallest subarray such that sum of the subarray is at least x and it is smallest possible in length
// O(n) solution using solution bag and two pointers, binary searching is also possible
pair <int, int> smallest_subarraysum_greater_than_x(vector <LL> &v, LL x) {
    deque <int> q = {0};
    vector <int> psum(v.size() + 1); // 1-indexed
    partial_sum(v.begin(), v.end(), psum.begin() + 1);
    // using min-queue as a solution bag
    auto insert = [&] (int id) {
        // sorts and hence allows binary search if needed
        while(!q.empty() and psum[q.back()] >= psum[id])
            q.pop_back();
        q.push_back(id);
    };
    auto latest_ans = [&](int id) {
        int ans = -1;
        // since it is sorted from smallest, if there are any solutions it will start from the front
        for(; !q.empty() and psum[id] - psum[q.front()] >= x; q.pop_front())
            ans = q.front();
        return ans;
    };
    int L = -1, R = v.size() + 1;
    for(int r = 0; r < v.size(); r++){
        int l = latest_ans(r + 1);
        if(l != -1 and r - l < R - L)
            L = l, R = r;
        insert(r + 1);
    }
    return {L, R}; // returned answer will be non-empty
} 

// Generic Cow Protests
// partition an array such that no partition has negative sum, how many ways
// another solution bag problem which uses deltaing, array compression and fenwick tree as the bag
// dp optimization
const LL mod = 1e9 + 9;
using m_int = INT_MOD <mod>;
m_int total_positive_paritions(vector <LL> &v) {
    int n = v.size();
    vector <LL> _v(n);
    LL delta = 0;
    ordered_set <LL> s;
    for(int i = 0; i < n; i++) {
        _v[i] = -delta, delta += v[i];
        s.insert(_v[i]);
    }
    BIT <m_int> T(n);
    T.add(s.order_of_key(0), 1);
    for(int i = 1; i < n; i++) {
        int id = s.order_of_key(_v[i]);
        m_int x = T.sum(id, n - 1);
        T.add(id, x);
    }
    return T.sum(s.order_of_key(-delta), n - 1);
}
int main()
{
    monke_flip
    int n;
    LL x;
    cin >> n >> x;
    vector <LL> a(n);
    for(auto &e:a){
        cin >> e;
    }
    dbg(smallest_subarraysum_greater_than_x(a, x));
    return MONKE;
}
