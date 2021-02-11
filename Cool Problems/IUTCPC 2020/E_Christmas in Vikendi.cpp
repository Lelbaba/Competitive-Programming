#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5;
ll tree[4*maxn];
ll height[maxn+5];
void innit(int l,int r,int node){
	if(l==r){
		tree[node] = height[l];
		return;
	}
	innit(l,(l+r)/2,2*node);
	innit((l+r+2)/2,r,2*node+1);
	tree[node] = max(tree[2*node],tree[2*node+1]);
}
ll query(int b,int e,int l,int r,int node){
	if(b>r || l>e) return -1;
	if(b<=l && r<=e) return tree[node];
	return max(query(b,e,l,(l+r)/2,2*node),query(b,e,(l+r+2)/2,r,2*node+1));
}

ll sum[4*maxn];
void create(int l,int r,int node){
	if(l==r){
		sum[node] = 0;
		return;
	}
	create(l,(l+r)/2,node*2);
	create((l+r+2)/2,r,node*2+1);
}
void update(int rank,int val,int l,int r,int node){
	if(l==r){
		if(l==rank)	sum[node]+=val;
		return;
	}
	int m = (l+r)/2;
	(rank<=m) ? update(rank,val,l,m,node*2) : update(rank,val,m+1,r,node*2+1);
	sum[node] = sum[node*2] + sum[node*2+1];
}
ll ask(int b,int e,int l,int r,int node){
	if(b>e) return 0;
	if(b>=l && r<=e) return sum[node];
	if(b>r || l>e) return 0;
	return ask(b,min(e,(l+r)/2),l,(l+r)/2,2*node)+ask(max(b,(l+r+2)/2),e,(l+r+2)/2,r,2*node+1);
}

void shops(int &N){
	cin>>N;
	for(int i=1;i<=N;i++){
		cin>>height[i];
	}
	innit(1,N,1);
}
vector <pair<int,ll> > buy(int &M,int N){
	cin>>M;
	int level,l,r;
	vector <ll> ht(M+1);
	vector <pair<int,ll> > ans(M);
	for(int i=0;i<M;i++){
		cin>>level>>l>>r;
		ll maxh = query(l,r,1,N,1);
		//printf("%d %d\n", level,maxh);
		ht[level] = maxh;
	}
	for(int i=0;i<M;i++){
		cin>>level;
		ans[i] = {level,ht[level]};
	}
	return ans;
}
void steal(vector <pair<int,ll> > &houses){
	int M = houses.size();
	create(1,M,1);
	vector <ll> ans(M);
	for(int i=M-1;i>=0;i--){
		int rank = houses[i].first;
		ll val = houses[i].second;
		ans[i] = ask(1,rank-1,1,M,1);
		update(rank,val,1,M,1);
	}
	for(auto x:ans) cout<<x<<" ";
}

int main()
{
	int n,m,t;
	cin>>t;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	while(t--){
		shops(n);
		auto v = buy(m,n);
		steal(v);
		cout<<endl;
	}
	return 0;
}
