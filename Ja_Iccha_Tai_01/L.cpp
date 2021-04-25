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
    int n,a,b,k;
    string s;
    cin>>n>>a>>b>>k;
    cin>>s;
    vector <int> hit,ans;
    hit.push_back(-1);
    for(int i=0;i<n;i++){
        if(s[i]== '1')
            hit.push_back(i);
    }
    hit.push_back(n);
    for(int i=0;i+1<hit.size();i++){
        for(int j=hit[i]+b;j<hit[i+1];j+=b)
            ans.push_back(j);
    }
    for(int i=1;i<a;i++)
        ans.pop_back();
    cout<<ans.size()<<'\n';
    for(auto x:ans)
        cout<<x+1<<" ";
    return MONKE;
}