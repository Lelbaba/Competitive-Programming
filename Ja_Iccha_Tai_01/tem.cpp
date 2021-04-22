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

int koto(int num,int n, int t){
    int r = num%n;
    int lagbe = ((t-r)%n + n )%n;
    return lagbe;
}
/*
    main idea is -
    ami pura array take 
    0 1 2 3 4 5... n-1 
    banai felbo
    tahole protita operation e ami ekdom last number theke shuru korbo and try
    korbo oitake  "i-th number(0 indexing) er shathe kichu ekta jog kore i(mod n) 
    banate".
    Last theke shuru korbo karon er ager index e ei operation use korle eitar
    upor effect thakbe na.  
    eita korar jonno joto jog kora lagbe shei number ta amake
    "koto" function ta dibe. 
    tahole

*/
int main()
{
    monke_flip
    int n;
    cin>>n;
    vector <int> v(n);
    for(auto &e:v){
        cin>>e;
    }
    int added = 0;
    int op = 1;
    vector <int> add(n+1);
    for(int i = n-1;i>=0;i--){
        int val = koto(v[i]+added,n,i);
        v[i] = (v[i] + val + added) % n;
        added += val;
        add[i+1] = val;
        if(val > 0) op++;
    }
    cout<<op<<'\n';
    for(int i = n; i>0; i--){
        if(add[i] == 0) continue;
        cout<<1<<' '<<i<<' '<<add[i]<<'\n';
    }
    cout<<2<<' '<<n<<' '<<n;
    return MONKE;
}