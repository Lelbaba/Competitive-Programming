#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int MONKE = 0;

using board = vector <vector <ll>>;

class node{
    public:
        ll id, depth, parent;
        board Board;
    node(board B = board(),ll _id = 0,ll _depth = 0, ll _parent = 0){
        Board = B, id = _id, depth = _depth, parent = _parent;
    }
    bool operator < (const node& N) const {
        return Board < N.Board;
    }
};
class solver{
    private:
        vector <node> v;
        queue <ll> Q;
        set <node> taken;
        const vector < vector <ll> > dir = {
            {1,0},
            {0,1},
            {-1,0},
            {0,-1}
        };
        const board terminal = {
            {0,1,2},
            {3,4,5},
            {6,7,8}
        };

    pair <ll,ll> empty_block(node &N){
        for(ll i=0; i<3; i++){
            for(ll j=0; j<3; j++){
                if(N.Board[i][j] == 0)
                    return make_pair(i,j);
            }
        }
        return make_pair(-1,-1);
    }
    bool valid(ll x,ll y){
        return (x>=0 and x<3 and y>=0 and y<3);
    }
    void moves(node N){
        auto tem = empty_block(N);
        ll x = tem.first, y = tem.second;
        for(auto e:dir){
            ll X = x+e[0], Y = y+e[1];
            auto tem_board = N.Board;
            if(valid(X,Y)){
                swap(tem_board[x][y], tem_board[X][Y]);
                if(taken.find(tem_board) == taken.end()){
                    ll id = v.size();
                    v.emplace_back(tem_board, id, N.depth+1,N.id);
                    taken.insert(v.back());
                    Q.push(id);
                }
            }
        }
    }
    ll BFS(board start, board end){
        v.emplace_back(start);
        Q.push(0);
        while(!Q.empty()){
            auto current = Q.front();
            Q.pop();
            if(v[current].Board == end)
                return current;
            moves(v[current]);
        }
        return -1;
    }
    void ugly_print(ll cur){
        cout<<"............\n";
        for(auto x:v[cur].Board){
            for(auto y:x){
                cout<<y<<" ";
            }
            cout<<'\n';
        }
    }
    public :
    solver(){
        board B = {{8,1,2},{0,4,3},{7,6,5}};
        BFS(terminal,B); //precompute
    }
    void path_finder(board B){
        auto it = taken.find(node(B));
        if(it == taken.end()){
            cout<<"THERE IS NO VALID SOLUTION\n";
        } else {
            for(ll id = it->id ; true; id = v[id].parent){
                ugly_print(id);
                if(id == 0) break;
            }
        } 
    }

};
int main()
{
    board B = {{1,2,3},{4,5,6},{7,8,0}};
    solver x;
    x.path_finder(B);
    return MONKE;
}