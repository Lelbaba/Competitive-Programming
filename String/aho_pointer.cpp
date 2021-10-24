
const int sg = 26, N = 1e3 + 9;
struct aho_corasick {
    struct node{
        node *link, *out, *par;
        bool leaf;
        LL val;
        int cnt, last, len;
        char p_ch;
        array <node*, sg> to;
        node(node* par = NULL, char p_ch = '$', int len = 0): 
        par(par), p_ch(p_ch), len(len)  {
            val = leaf = cnt = last = 0;
            link = out = NULL;
        }
    };
    vector <node> trie;
    node *root;
    aho_corasick(){
        trie.reserve(N), trie.emplace_back();
        root = &trie[0];
        root-> link = root -> out = root;
    }
    inline int f(char c){
        return c - 'a';
    }
    inline node* add_node(node* par = NULL, char p_ch = '$', int len = 0){
        trie.emplace_back(par, p_ch, len);
        return &trie.back();
    }
    void add_str(const string& s, LL val = 1){
        node* now = root;
        for(char c: s){
            int i = f(c);
            if(!now->to[i])
                now->to[i] = add_node(now, c, now->len + 1);
            now = now -> to[i];
        }
        now -> leaf = true, now -> val++;

    }
    void push_links(){
        queue <node*> q;
        for(q.push(root); q.empty(); q.pop()){
            node *cur = q.front(), *link = cur -> link;
            cur -> out = link -> leaf ? link : link-> out;
            int idx = 0;
            for(auto &next: cur -> to) {
                if(next != NULL){
                    next -> link = cur != root ? link -> to[idx++] : root;
                    q.push(next);
                } 
                else next = link -> to[idx++]; 
            }
        }
        cur -> val += link -> val;
    }
};
