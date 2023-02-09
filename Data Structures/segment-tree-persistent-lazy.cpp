#include <bits/stdc++.h>
using namespace std;
using LL = long long;
// needs to be tested properly
struct Node {
    const int val, lazy;
    Node* const lft, *const ryt;
    Node(const int val = 0, const int lazy = 0, Node* const lft = NULL, Node* const ryt = NULL) : val(val), lazy(lazy), lft(lft), ryt(ryt) {}
    Node(Node* const lft, Node* const ryt, int lazy = 0) : val(lft -> val + ryt -> val), lazy(lazy), lft(lft), ryt(ryt) {}
    ~Node(){
        if(lft != NULL) delete lft;
        if(ryt != NULL) delete ryt;
    }
};
Node* const build(const int L, const int R, const vector <int> &v) {
    if(L == R) return new Node(v[L]);
    const int M = L + R >> 1;
    return new Node(build(L, M, v), build(M + 1, R, v));
}
const int query(const int ql, const int qr, Node* const cur, const int L, const int R, const int prop = 0) {
    if(ql > R or qr < L) return 0;
    if(ql <= L and R <= qr) return cur -> val + prop * (R - L + 1);
    const int M = L + R >> 1;
    return query(ql, qr, cur -> lft, L, M, prop + cur -> lazy) + 
        query(ql, qr, cur -> ryt, M + 1, R, prop + cur -> lazy);
}
Node* const update(const int ql, const int qr, const int up, Node* const cur, const int L, const int R) {
    if(ql > R or qr < L) return cur;
    if(ql <= L and R <= qr) return new Node(cur -> val + up * (R - L + 1), cur -> lazy + up, cur -> lft, cur -> ryt);
    const int M = L + R >> 1;
    return new Node(update(ql, qr, up, cur -> lft, L, M), update(ql, qr, up, cur -> ryt, M + 1, R), cur -> lazy);
}
int main(){
    vector <int> v = {2, 1, 5, 3, 4};
    vector <Node*> roots;
    roots.push_back(build(0, 4, v));
    cout << query(0, 2, roots.back(), 0, 4) << '\n';
    roots.push_back(update(1, 3, 2, roots.back(), 0, 4));
    cout << query(0, 2, roots.back(), 0, 4) << '\n';
    cout << query(0, 2, roots[0], 0, 4) << '\n';
    while(!roots.empty()) {
        delete roots.back();
        roots.pop_back();
    }
}
