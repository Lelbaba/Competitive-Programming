namespace sieve{
    const int maxn = 1e7;
    vector <int> primes;
    int spf[maxn+5], phi[maxn+5], NOD[maxn+5], cnt[maxn+5], POW[maxn+5]; 
    bool prime[maxn+5];
    int SOD[maxn+5];
    void init(){
        fill(prime+2, prime+maxn+1, 1);
        SOD[1] = NOD[1] = phi[1] = spf[1] = 1;
        for(ll i=2;i<=maxn;i++){
            if(prime[i]) {
                primes.push_back(i), spf[i] = i;
                phi[i] = i-1;
                NOD[i] = 2, cnt[i] = 1;
                SOD[i] = i+1, POW[i] = i;
            }
            for(auto p:primes){
                if(p*i>maxn or p > spf[i]) break;
                prime[p*i] = false, spf[p*i] = p;
                if(i%p == 0){
                    phi[p*i]=p*phi[i];
                    NOD[p*i]=NOD[i]/(cnt[i]+1)*(cnt[i]+2), cnt[p*i]=cnt[i]+1;
                    SOD[p*i]=SOD[i]/SOD[POW[i]]*(SOD[POW[i]]+p*POW[i]),POW[p*i]=p*POW[i];
                    break;
                } else {
                    phi[p*i]=phi[p]*phi[i];
                    NOD[p*i]=NOD[p]*NOD[i], cnt[p*i]=1;
                    SOD[p*i]=SOD[p]*SOD[i], POW[p*i]=p;
                }

            }
        }
    }
    // O(lg n factorization for small numbers upto sieve)
    map <ull,int> fast_factorize(ull n){
        map <ull,int> ans;
        for(;n>1;n/=spf[n])
            ans[spf[n]]++;
        return ans;
    }
    // factorization for big numbers
    // using poullard rho might be better
    map <ull,int> factorize(ull n){
        int cnt = 0;
        map <ull,int> ans;
        for(auto p:primes){
            if(p*p>n) break;
            for(;n%p==0;n/=p)
                ans[p]++;
        }
        if(n!=1) ans[n]++;
        return ans;
    }
    // only for large numbers
    int number_of_div(ull n){
        if(n < 1) return 0;
        auto A = factorize(n);
        int ans = 1;
        for(auto [p,cnt]:A)
            ans *= cnt+1;
        return ans;
    }
    ull sum_of_div(ull n){
        if(n < 1) return 0;
        ull ans = 1, ppow;
        for(ull p:primes){
            if(p*p > n) break;
            for(ppow=p; n%p==0; n/=p,ppow*=p);
            ans *=(ppow-1)/(p-1);
        }
        return n == 1 ? ans: ans*(1+n);
    }
    ull PHI(ull n){
        ull ans = n;
        for(auto [p,cnt]:factorize(n))
            ans = ans/p*(p-1); 
        return ans;
    }
}
