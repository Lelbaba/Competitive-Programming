#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke chrono::system_clock::now().time_since_epoch().count()
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using ll = long long;
const int MONKE = 0;

double mat[30][30], eps = 1e-19;
double gaussian_elimination(int row, int col){
    int basis[30];
    memset(basis,-1,sizeof basis);
    
    double det = 1;
    for(int i = 0; i < col; i++){
        int &x = basis[i];
        for(int k = 0; k < row; k++){
            if(abs(mat[k][i]) > eps){
                x = k, det *= mat[k][i];
                break;
            }
        }
        if(x < 0) continue;
        for(int j = 0; j < col; j++)
            if(j != i)  for(int k = 0; k < row; k++) if(k != x) 
                mat[k][j] -= (mat[k][i] * mat[x][j])/ mat[x][i];
        for(int k = 0; k < row; k++) if(k != x)
            mat[k][i]/= mat[x][i];
        for(int j = 0; j < col; j++)
            mat[x][j] = (j==i);
    }

    return det;
}

int main()
{
    monke_flip
    mat[0][0] = 0, mat[0][1] = 6, mat[1][0] = 0, mat[1][1] = 20;
    cout << gaussian_elimination(2,2);
    return MONKE;
}