#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll tree[300005];
ll prop[300005];
void update(int l,int r,int b,int e,ll num,int node){
	if(e<l || b>r)	return;
	if(b<=l && r<=e){
		tree[node]+= num*(r-l+1);
		prop[node]+= num;
		return;
	}
	update(l,(l+r)/2,b,e,num,node*2);
	update((l+r+2)/2,r,b,e,num,node*2+1);
	tree[node] = tree[node*2] + tree[node*2+1] +prop[node]*(r-l+1);
}
ll query(int l,int r,int b,int e,int node,ll carry){
	if(b>r || e<l) return 0;
	if(b<=l && r<=e){
		return (tree[node] + (r-l+1)*carry);
	}
	return query(l, (l+r)/2, b, e,node*2, carry + prop[node]) + 
		   query((l+r+2)/2,r, b, e,node*2+1, carry + prop[node]);
}
int main()
{
	int t;
	scanf("%d", &t);
	for(int tc=1; tc<=t; tc++){
		int n,q,i,j,k; ll v;

		memset(tree,0,sizeof tree);
		memset(prop,0,sizeof prop);
		
		scanf("%d%d", &n,&q);
		//printf("Case %d:\n",tc);
		
		while(q--){
			scanf("%d",&k);
			if(k) {
				scanf("%d%d",&i,&j);
				i--;j--;
				ll ans = query(0,n-1,i,j,1,0);
				printf("%lld\n", ans);
			}
			else {
				scanf("%d %d %lld", &i, &j, &v);
				i--;j--;
				update(0,n-1,i,j,v,1);
			}
		}
	}
	return 0;
}
