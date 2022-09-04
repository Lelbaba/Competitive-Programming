#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 20, B = 26, del = 'a';
/*
prefix automaton allows insertion to prefix function in O(1) time;
tested in CF 1721 E
*/
struct prefix_automaton {
    int n;
    vector <int> fail;
    vector <array<int, B>> f;
    prefix_automaton(const string &s) : n(s.size()), fail(n + 11), f(n + 11, {0}){
        fail[0] = 0, f[0][s[0] - del] = 1;
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < B; j++) {
                if(j == s[i] - del) f[i][j] = i + 1, fail[i] = f[fail[i - 1]][j];
                else f[i][j] = f[fail[i - 1]][j];
            }
        }
    }
    void push(char ch) {
        for(int j = 0; j < 26; j++) {
            if(j == ch - del) f[n][j] = n + 1, fail[n] = f[fail[n - 1]][j];
            else f[n][j] = f[fail[n - 1]][j];
        }
        n++;
    }
    void push(const string &s) {
        for(auto e: s) push(e);
    }
    // pop until size of string is smaller or equal to sz
    void pop(int sz) {
        n = sz;
    }
};
int main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    int n = s.size(), q;
    prefix_automaton T(s);
    cin >> q;
    while(q--) {
        string x;
        cin >> x;
        T.push(x);
        for(int i = 0; i < x.size(); i++) {
            cout << T.fail[i + n] << ' ';
        }
        cout << '\n';
        T.pop(n);
    }
    return 0;
}
