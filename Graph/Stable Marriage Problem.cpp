#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;
using ll = long long;
const int MONKE = 0;
//UVA 11119
map <string,int> cat,an;
int C[105][105],A[105][105];
string _cat[105],_an[105];

void input_chemicals(int n){
	cat.clear();
	an.clear();
	for(int i=0;i<n;i++){
		cin>>_cat[i];
		cat[_cat[i]] = i;
	}
	int m;
	cin>>m;
	for(int i=0;i<m;i++){
		cin>>_an[i];
		an[_an[i]] = i;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>C[i][j];
		}
	}
	for(int j=0;j<m;j++){
		for(int i=0;i<n;i++){
			cin>>A[j][i];
		}
	}
}

bool check_stability(vector <int> &CAT, vector <int> &AN){
	int n = CAT.size();
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			int c = CAT[j],a = AN[j],cc = CAT[i],aa = AN[i];
			if(C[cc][a]>C[cc][aa] && A[a][cc]>A[a][c]) return false;
		}
	}
	return true;
}

void stablize(vector <int> &CAT,vector <int> &AN){
	if(check_stability(CAT,AN)) return;

	int n = CAT.size();
	vector <int> eng(n,-1);
	vector <int> tem(n);
	for(int i=0;i<n;i++){
		tem[i] = i;
	}
	vector < vector <int> > prio(n,tem);
	for(int i=0;i<n;i++){
		sort(prio[i].begin(),prio[i].end(),[&](int x,int y){return C[CAT[i]][AN[x]]<C[CAT[i]][AN[y]];});
	}
	queue <int> bachelor;
	for(int i=0;i<n;i++){
		bachelor.push(i);
	}
	while(!bachelor.empty()){
		int man = bachelor.front();
		int woman = prio[man].back();
		prio[man].pop_back();
		if(eng[woman]==-1 || A[AN[woman]][CAT[man]]>A[AN[woman]][CAT[eng[woman]]]){
			
			if(eng[woman] != -1){
				bachelor.push(eng[woman]);
			}
			eng[woman] = man;
			bachelor.pop();
		}
	}
	//for(auto x:baki) cout<<_cat[x]<<endl;
	for(int i=0;i<n;i++){
		tem[i] = CAT[eng[i]];
	}
	for(int i=0;i<n;i++){
		CAT[i] = tem[i];
	}
	assert(check_stability(CAT,AN));
}

void input_compunds(int n,vector <int> &CAT,vector <int> &AN){
	string cmp;
	CAT.clear();
	AN.clear();
	for(int i=0;i<n;i++){
		cin>>cmp;
		string na,cl;
		na = cmp.substr(0,2);
		cl = cmp.substr(2,2);
		CAT.push_back(cat[na]);
		AN.push_back(an[cl]);
	}

}
void solve(int n,int sc){
	input_chemicals(n);
	vector <int> CAT,AN;
	int c;
	int mix = 1;
	while(true){
		cin>>c;
		if(!c) break;
		input_compunds(c,CAT,AN);
		stablize(CAT,AN);
		cout<<"Scenario "<<sc<<", Mixture "<<mix<<":"<<endl;
		for(int i=0;i<c;i++){
			cout<<_cat[CAT[i]]<<_an[AN[i]]<<" ";
		}
		cout<<"\n\n";
		mix++;
	}
}

int main()
{
	fastio
	int t = 1,sc=1; 
	while(true){
		int n;
		cin>>n;
		if(!n) break;
		solve(n,sc);
		sc++;
	}
	return MONKE;
}