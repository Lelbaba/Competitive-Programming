#include <bits/stdc++.h>
using namespace std;
using LL = long long;

/*....................................................................*/

/*....................................................................*/
const int sg = 26, N = 5e5 + 9;

struct AhoCorasick {

    struct Node{
        Node *link, *out, *par;
        bool leaf;
        LL val;
        int len, idx;
        char p_ch;
        array <Node*, sg> to = {0};
        Node(Node* par = NULL, char p_ch = '$', int len = 0): 
        par(par), p_ch(p_ch), len(len)  {
            val = leaf = 0;
            link = out = NULL;
            idx = -1;
        }
    };

    Node trie[N], *root;
    int ptr = 0;

    AhoCorasick(){
        root = &trie[0];
        ptr = 1;
        root-> link = root -> out = root;
        for(auto &e : root->to) {
            e = NULL;
        }
    }
    int f(char c){
        return c - 'a';
    }
    Node* addNode(Node* par = NULL, char p_ch = '$', int len = 0){
        trie[ptr] = Node(par, p_ch, len);
        return &trie[ptr++];
    }
    void addPattern(const string& s, Node* &ptr, LL val = 1){
        Node* now = root;
        for(char c: s){
            int i = f(c);
            if(!now->to[i])
                now->to[i] = addNode(now, c, now->len + 1);
            now = now -> to[i];
        }
        now -> leaf = true, now -> val = val;
        ptr = now;
 
    }
    void pushLinks(){
        queue <Node*> q;
        for(q.push(root); !q.empty(); q.pop()){
            Node *now = q.front(), *link = now -> link;
            now -> out = link -> leaf ? link : link-> out;
            int idx = 0;
            for(auto &next: now -> to) {
                if(next != NULL){
                    next -> link = now != root ? link -> to[idx] : root;
                    q.push(next);
                } 
                else next = link -> to[idx] == NULL ? root : link -> to[idx]; 
                idx++;
            }
            now -> val += link -> val;
        }
    }

    LL count(const string &s){
        LL ans = 0;
        Node* now = root; 
        for(auto &c: s){
            now = now -> to[f(c)];
            ans += now -> val;
        }
        return ans;
    }

    void traverse(const string &s){
        Node* now = root;
        /* Traversing the automata, when a pattern is found, check if the current length is smaller 
         * than the pattern length*/  
        int idx = 0;
        for(auto &c: s){
            now =  now -> to[f(c)], idx++;
            for(Node* v = now; v != root; v = v->out)
                if(v -> idx == -1) v -> idx = idx - v -> len + 1;
        }
    }
};
 
int main() {
    cin.tie(0) -> sync_with_stdio(0);

    string s;
    cin >> s;

    AhoCorasick T;

    int k;
    cin >> k;
    vector <pair <string, AhoCorasick :: Node*>> patterns(k);

    for(auto &[pat, u]: patterns) {
        cin >> pat;
        T.addPattern(pat, u);
    }
    T.pushLinks();
    T.traverse(s);
    for(auto &[pat, u] : patterns) {
        cout << u -> idx << '\n';
    }

}