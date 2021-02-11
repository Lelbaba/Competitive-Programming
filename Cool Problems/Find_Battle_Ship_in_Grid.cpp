#include <bits/stdc++.h>
using namespace std;

int mat[8][8];
int dp[5][5][5][5];
int path[5][5][5][5];
int max_query(int u,int d,int l,int r){
	int &ans = dp[u][d][l][r];
	if(ans!=-1)	return ans;
	if(l==0 && r==0){
		path[u][d][l][r] = 0;
		return ans = max(u+d-3,0);
	}
	if(u==0 && d==0){
		path[u][d][l][r] = 0;
		return ans = max(l+r-3,0);
	}
	int temp = 89,x;
	if(u>0){
		x = max(max_query(u,min(d,2),0,0),max_query(0,d,l,r));
		if(x<temp){
			temp = x;
			path[u][d][l][r] = 1;
		}
	}
	if(d>0){
		x = max(max_query(min(u,2),d,0,0),max_query(u,0,l,r));
		if(x<temp){
			temp = x;
			path[u][d][l][r] = 2;
		}
	}
	if(l>0){
		x = max(max_query(0,0,l,min(r,2)),max_query(u,d,0,r));
		if(x<temp){
			temp = x;
			path[u][d][l][r] = 3;
		}
	}
	if(r>0){
		x = max(max_query(0,0,min(l,2),r),max_query(u,d,l,0));
		if(x<temp){
			temp = x;
			path[u][d][l][r] = 4;
		}
	}
	return ans=temp+1;
}
void Call(int R,int C,int u,int d,int l,int r){
	char ch;
	if(path[u][d][l][r]==1){
		cout<<"? "<<R-1<<" "<<C<<endl<<flush;
		cin>>ch;
		(ch=='S') ? Call(R,C,u,min(d,2),0,0):Call(R,C,0,d,l,r);
	}
	else if(path[u][d][l][r]==2){
		cout<<"? "<<R+1<<" "<<C<<endl<<flush;
		cin>>ch;
		(ch=='S') ? Call(R,C,min(u,2),d,0,0):Call(R,C,u,0,l,r);
	}
	else if(path[u][d][l][r]==3){
		cout<<"? "<<R<<" "<<C-1<<endl<<flush;
		cin>>ch;
		(ch=='S') ? Call(R,C,0,0,l,min(r,2)):Call(R,C,u,d,0,r);
	}
	else if(path[u][d][l][r]==4){
		cout<<"? "<<R<<" "<<C+1<<endl<<flush;
		cin>>ch;
		(ch=='S') ? Call(R,C,0,0,min(l,2),r):Call(R,C,u,d,l,0);
	}
	else if(u+d==3){
		cout<<"! "<<R-u<<" "<<C<<" "<<R+d<<" "<<C<<endl<<flush;
		return;
	}
	else if(l+r==3){
		cout<<"! "<<R<<" "<<C-l<<" "<<R<<" "<<C+r<<endl<<flush;
	}
	else if(l+r==0){
		int rr = R;
		if(u>d) rr = R-u;
		else rr = R+d;
		cout<<"? "<<rr<<" "<<C<<endl<<flush;
		cin>>ch;
		if(u>d){
			if(ch=='S'){
				cout<<"! "<<rr<<" "<<C<<" "<<rr+3<<" "<<C<<endl<<flush;
			}
			else Call(R,C,u-1,d,l,r);
		}
		else{
			if(ch=='S') cout<<"! "<<rr-3<<" "<<C<<" "<<rr<<" "<<C<<endl<<flush;
			else Call(R,C,u,d-1,l,r);
		}
	}
	else{
		int cc = C;
		if(l>r) cc = C-l;
		else cc = C+r;
		cout<<"? "<<R<<" "<<cc<<endl<<flush;
		cin>>ch;
		if(l>r){
			if(ch=='S') cout<<"! "<<R<<" "<<cc<<" "<<R<<" "<<cc+3<<endl<<flush;
			else Call(R,C,u,d,l-1,r);
		}
		else{
			if(ch=='S') cout<<"! "<<R<<" "<<cc-3<<" "<<R<<" "<<cc<<endl<<flush;
			else Call(R,C,u,d,l,r-1);
		}
	}
}
bool query(int R,int C){
	char ch;
	cout<<"? "<<R<<" "<<C<<endl<<flush;
	cin>>ch;
	if(ch=='W') return false;
	int u = min(R-1,3);
	int d = min(7-R,3);
	int l = min(C-1,3);
	int r = min(7-C,3);
	Call(R,C,u,d,l,r);
	return true;
}
int depth(int R,int C){
	int u = min(R-1,3);
	int d = min(7-R,3);
	int l = min(C-1,3);
	int r = min(7-C,3);
	return max_query(u,d,l,r);
}
struct cell
{
	int r,c;
	cell(int R,int C){
		r = R; c = C;
	}
	bool operator < (const cell& rhs) const{
		return depth(r,c)>depth(rhs.r,rhs.c);
	}
};

int main()
{
	int i,j,k,m,n;
	vector <cell>  v;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			if((i+j)%4==0){
				v.push_back({i+1,j+1});
			}
		}
	}

	memset(dp,-1,sizeof dp);
	sort(v.begin(), v.end());
	auto last = v.back();
	v.pop_back();
	int T;
	cin>>T;
	while(T--){
		bool f = false;
		for(auto x:v){
			f = query(x.r,x.c);
			if(f) break;
		}
		if(!f){
			int u = min(last.r-1,3);
			int d = min(7-last.r,3);
			int l = min(last.c-1,3);
			int r = min(7-last.c,3);
			Call(last.r,last.c,u,d,l,r);
		}
	}
	return 0;
}
