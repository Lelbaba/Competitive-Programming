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
	
	string s1,s2,s;
	int n,d;

	cin>>n>>d>>s1>>s2;
	string ans = s1;
	bool flag = false;
	int cnt_1 = 0, cnt_2 = 0;
	
	for(int i=0; i<n; i++){
		if(ans[i] != s2[i]){
			if(flag) ans[i] = s2[i], cnt_1++;
			else cnt_2++;
			flag^= 1;
		}
	}
	if(cnt_2>d){
		cout<<-1;
	} else{
		for(int i=0; i<n; i++){
			if(s1[i] == s2[i] and cnt_1 < d and cnt_2 < d){
				for(char c='a';c<='z';c++){
					if(s1[i] != c and s2[i]!= c){
						ans[i] = c;
						break;
					}
				}
				cnt_1++, cnt_2++;
			}
			else if(s1[i] == ans[i] and s2[i]!=ans[i] and cnt_1 < d){
				for(char c='a';c<='z';c++){
					if(s1[i] != c and s2[i]!= c){
						ans[i] = c;
						break;
					}
				}
				cnt_1++;
			}
			else if(s2[i] == ans[i] and s1[i]!= ans[i] and cnt_2 < d){
				for(char c='a';c<='z';c++){
					if(s1[i] != c and s2[i]!= c){
						ans[i] = c;
						break;
					}
				}
				cnt_2++;
			}
		}
		cout<<ans;
	}
	return MONKE;
}