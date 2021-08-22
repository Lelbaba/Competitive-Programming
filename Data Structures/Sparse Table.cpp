#include <bits/stdc++.h>
using namespace std;
/*
	The problem asks - given ar array, the minimum number of distinct subsequences such that 
	1. both end points have the same numbers
	2. all numbers inside are greater or equal ro the points.
	3. all numbers in the arrays are part of some subsequence.
*/
using LL = long long;
const int maxn = (1<<20)+5 ;
int logs[maxn];

void compute_logs(){
	logs[1] = 0;
	for(int i=2;i<(1<<20);i++){
		logs[i] = logs[i/2]+1;
	}
}
vector <vector <int> >  build_table(vector <int> &v){
	int sz = v.size();
	vector <int> tem(25);
	vector <vector <int> > table(sz+2,tem);

	for(int j=0;j<=logs[sz];j++){
		for(int i=0;i+(1<<j)<=sz;i++){
			if(j==0) table[i][j] = v[i];
			else table[i][j] = min(table[i][j-1], table[i + (1<<(j-1))][j-1] );
		}
	}
	return table;
}
int getMin(int l, int r, vector <vector <int> > &table) {
	int pow = logs[r - l + 1];
	int Len = 1 << pow; 
	return min(table[l][pow], table[r- Len + 1][pow]);
}
int main()
{
	int n;
	compute_logs();
	int tc = 1;
	map <int,vector <int> > V;
	set <int> S;	
	while(cin>>n){
		V.clear();
		S.clear();
		vector <int> arr(n);
		for(int i=0;i<n;i++){
			cin>>arr[i];
			if(arr[i]==0) continue;
			S.insert(arr[i]);
			V[arr[i]].push_back(i);
		}
		auto table = build_table(arr);
		for(auto x:S) sort(V[x].begin(),V[x].end());
		int ans = S.size();
		for(auto x:S){
			auto &v = V[x];
			int tem = 0;
			for(int i=1;i<v.size();i++){
				//printf("%d %d %d\n",v[i-1],v[i],getMin(v[i-1],v[i]) );
				if(getMin(v[i-1],v[i],table) < x) tem++;
			}
			ans+=tem;
		}
		printf("Case %d: %d\n",tc, ans);
		tc++;
	}
	return 0;
}
