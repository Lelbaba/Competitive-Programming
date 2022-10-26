#include <bits/stdc++.h>
using namespace std;
/*
tested in https://judge.yosupo.jp/submission/110003
line 54: a character smaller than the alphabet must be added for suffix array of string, becomes 1-indexed.
otherwise sorts cyclic shifts.

*/
namespace SA {
    const int B = 27, N = 1e6 + 5;
    char del = 'a' - 1;
    int p[N], c[N], cnt[N], _p[N], _c[N], lcp[N];
    void suffix_array (const string &s) {
        int n = s.size(), cmax = max(n, B);
        for(char x: s) cnt[x - del]++;
        partial_sum(cnt, cnt + cmax, cnt);
        for(int i = n - 1; ~i; i--) p[--cnt[s[i] - del]] = i;
        c[p[0]] = 0;
        for(int i = 1; i < n; i++) c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]); 
        fill(cnt, cnt + c[p[n - 1]] + 1, 0);

        for(int h = 1; h < n; h <<= 1) {
            cmax = c[p[n - 1]] + 1;
            for(int i = 0; i < n; i++) _p[i] = (p[i] + n - h) % n;
            for(int i = 0; i < n; i++) cnt[c[i]]++;
            partial_sum(cnt, cnt + cmax, cnt);
            for(int i = n - 1; ~i; i--) p[--cnt[c[_p[i]]]] = _p[i];
            _c[p[0]] = 0;
            for(int i = 1; i < n; i++) {
                auto prev = make_pair(c[p[i - 1]], c[(p[i - 1] + h) % n]);
                auto nxt = make_pair(c[p[i]], c[(p[i] + h) % n]);
                _c[p[i]] = _c[p[i - 1]] + (prev != nxt);         
            }
            fill(cnt, cnt + _c[p[n - 1]] + 1, 0);
            swap(c, _c);
        } 
        for(int i = 0; i < n; i++) _p[p[i]] = i;
    }
    void lcp_array(const string &s) {
        int n = s.size();
        for(int i = 0, k = 0; i < n; i++, k = max(0, k - 1)) {
            if(_p[i] != n - 1) {
                for(int j = p[_p[i] + 1]; i + k < n and j + k < n and s[i + k] == s[j + k]; k++);
                lcp[_p[i]] = k;
            } else k = 0;
        }
    }
}

int main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    long long ans = s.size() * (s.size() + 1) / 2;
    s += SA :: del;
    SA :: suffix_array(s);
    SA :: lcp_array(s);
    for(int i = 1; i + 1 < s.size(); i++) ans -= SA :: lcp[i];
    cout << ans << '\n';
}