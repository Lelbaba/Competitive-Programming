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

ll abs(modulo_int a){
    return abs(a.val);
}
double eps = 1e-19;
template <typename DT> using matrix = vector <vector <DT>>;

template <typename TYPE>
struct Gauss{
    int row = 0, col = 0, dependant = 0;
    vector <int> basis;
    matrix <TYPE> data, aug;
    vector <int> ans;
    TYPE det = 1;
    Gauss(matrix <TYPE> data) : row(data.size()), col(data[0].size()), data(data) {
        basis.assign(col, -1);
    }
    void append(vector <TYPE> v){
        assert(v.size() == col);
        aug.push_back(v);
    }
    vector <pair <int, vector <TYPE>>> gaussian_elimination(){
        int extra = aug.size();
        vector <pair <int, vector <TYPE>>> sol(extra);
        auto mat = data;
        for(auto &e: aug)
            mat.push_back(e);
        for(int i = 0; i < row; i++){
            int x = -1;
            for(int k = 0; k < col; k++){
                if(abs(mat[i][k]) > eps and basis[k] == -1){
                    x = k, det *= mat[i][k], basis[x] = i;
                    break;
                }
            }
            if(x < 0){
                dependant++;
                continue;
            }
            for(int j = 0; j < row + extra; j++)
                if(j != i)  for(int k = 0; k < col; k++) if(k != x) 
                    mat[j][k] -= (mat[i][k] * mat[j][x])/ mat[i][x];
            for(int k = 0; k < row + extra; k++) if(k != i)
                mat[k][x]/= mat[i][x];
            for(int j = 0; j < col; j++)
                mat[i][j] = (j==i);
        }
        for(int k = 0; k < col; k++)
            if(basis[k] == -1)
                det = 0;
        int idx = row;
        for(auto &[ans, s]: sol){
            ans = dependant > 0 ? -1 : 1;
            s = mat[idx++];
            for(int i = 0; i < col; i++)
                if(basis[i]== -1 and abs(s[i]) > eps ){
                    ans = 0;
                    break;
                }
        }
        aug.clear();
        return sol;
    }
};
double MAT[30][30], eps = 1e-19;
double gaussian_elimination(int row, int col){
    int basis[30];
    for(int j = 0; j < row; j++){
        MAT[j][j+col] = 1;
    }
    memset(basis,-1,sizeof basis);
    double det = 1;
    for(int i = 0; i < col; i++){
        for(int p = 0; p < row ; p++){
            for(int q = 0; q < col; q++)
                cout << MAT[p][q] << ' ';
            cout << '\n';
        }
        int x = -1;
        for(int k = 0; k < row; k++){
            if(abs(MAT[k][i]) > eps and basis[k] == -1){
                x = k, det *= MAT[k][i], basis[x] = i;
                break;
            }
        }
        if(x < 0) continue;
        for(int j = 0; j < col; j++)
            if(j != i)  for(int k = 0; k < row; k++) if(k != x) 
                MAT[k][j] -= (MAT[k][i] * MAT[x][j])/ MAT[x][i];
        for(int k = 0; k < col; k++) if(k != i)
            MAT[x][k]/= MAT[x][i];
        for(int j = 0; j < row; j++)
            MAT[j][i] = (j==i);
    }
    for(int i = 0; i < row ; i++){
        for(int j = 0; j < col; j++)
            cout << MAT[i][j] << ' ';
        cout << '\n';
    }
    for(int k = 0; k < row; k++)
        if(basis[k] == -1)
            return 0;
    return det;
}

int main()
{
    monke_flip
    MAT[0][0] = 5, MAT[0][1] = 6, MAT[1][0] = 0, MAT[1][1] = 20;
    cout << gaussian_elimination(2,2);
    return MONKE;
}