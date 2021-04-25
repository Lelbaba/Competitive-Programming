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

int main()
{
    monke_flip
    int n;
    cin>>n;
    vector <int> v(n),l(n),r(n),ans(n);
    for(auto &e:v)
        cin>>e;
    stack <int> L,R;
    for(int i=0;i<n;i++){
        while(!L.empty() and v[L.top()]>=v[i])
            L.pop();
        l[i] = L.empty() ? 0 : L.top()+1;
        L.push(i);
    }
    for(int i=n-1;i>=0;i--){
        while(!R.empty() and v[R.top()]>=v[i])
            R.pop();
        r[i] = R.empty() ? n-1 : R.top()-1;
        R.push(i);
    }
    for(int i=0;i<n;i++){
        ans[r[i]-l[i]] = max(ans[r[i]-l[i]], v[i]);
    }
    partial_sum(ans.rbegin(),ans.rend(),ans.rbegin(),[](int a,int b){return max(a,b);});
    for(auto x:ans) cout<<x<<" ";
    return MONKE;
}