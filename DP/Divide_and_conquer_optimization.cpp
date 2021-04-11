#include <bits/stdc++.h>

#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
#ifdef LEL
#include "dbg.h"
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using ll = long long;
const int MONKE = 0;

const int maxn = 1e5+5;
ll dp[maxn][2],total = 0;
int opt[maxn][2], arr[maxn],cnt[maxn];
int N,L = 1,R = 0;
bool vis[maxn];

void check(int idx){
	if(vis[idx]){
		vis[idx] = false;
		cnt[arr[idx]]--;
		total -= cnt[arr[idx]];
	} else {
		vis[idx] = true;
		total += cnt[arr[idx]];
		cnt[arr[idx]]++;
	}
}
ll cost(int l,int r){
	while(L > l) check(--L);
	while(L < l) check(L++);
	while(R > r) check(R--);
	while(R < r) check(++R);
	return total;
}

void init(int n){
	N = n;
	memset(vis,false,sizeof vis);
	memset(cnt,0,sizeof cnt);

	for(int i=0;i<maxn;i++){
		dp[i][1] = cost(1,i);
	}
}

void conquer(int k,int l =1,int r = N,int optl = 0,int optr = N){
	if(r<l) return;
	k = k&1;
	int mid = l+r >> 1;
	dp[mid][k] = LLONG_MAX;
	int optm = -1;
	for(int last = optl;last <=optr && last <mid; last++){
		ll val = dp[last][k^1]+cost(last+1,mid);
		if(val < dp[mid][k]){
			dp[mid][k] = val;
			optm = last;
		}
	}
	conquer(k,l,mid-1,optl,optm);
	conquer(k,mid+1,r,optm,optr);
}

int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
	}

	init(n);
	for(int i=2;i<=k;i++){
		conquer(i);
	}
	cout<<dp[n][k&1]<<endl;
	return MONKE;
}