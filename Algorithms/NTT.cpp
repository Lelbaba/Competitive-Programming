#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1004535809, mod_g = 3, img = 86583718;
#define Inv(x) quick_pow(x, mod - 2)
#define Polynomial vector<ll>

int quick_pow(int ans, int p, int res = 1) {
    for(; p; p >>= 1, ans = (ll)ans * ans % mod)
        if(p & 1) res = (ll)res * ans % mod;
    return res % mod;
}

namespace NTT_ {
    Polynomial R;
//二进制向上取整，为方便NTT变换准备。
    inline int Binary_Rounding(const int &n, int len = 1) {
        while (len < n) len <<= 1;
        return len;
    }
//预处理R数组，准备变换，在每次NTT之前理论都要调用此函数。
    inline int Prepare_Transformation(int n) {
        int L = 0, len;
        for (len = 1; len < n; len <<= 1) L++;
        R.clear();
        R.resize(len);
        for (int i = 0; i < len; ++i)
            R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
        return len;
    }
    inline void NTT(Polynomial &a, int f) {
        int n = a.size();
        for (int i = 0; i < n; ++i)
            if (i < R[i])swap(a[i], a[R[i]]);
        for (int i = 1; i < n; i <<= 1)
            for (int j = 0, gn = quick_pow(mod_g, (mod - 1) / (i << 1)); j < n; j += (i << 1))
                for (int k = 0, g = 1, x, y; k < i; ++k, g = 1ll * g * gn % mod)
                    x = a[j + k], y = 1ll * g * a[i + j + k] % mod,
                    a[j + k] = (x + y) % mod, a[i + j + k] = (x - y + mod) % mod;
        if (f == -1) {
            reverse(a.begin() + 1, a.end());
            int inv = Inv(n);
            for (int i = 0; i < n; ++i) a[i] = 1ll * a[i] * inv % mod;
        }
    }
    inline Polynomial operator+(const Polynomial &a, const int &b) {
        int sizea = a.size();
        Polynomial ret = a;
        ret.resize(sizea);
        for (int i = 0; i < sizea; ++i)ret[i] = (1ll * a[i] + b + mod) % mod;
        return ret;
    }
    inline Polynomial operator-(const Polynomial &a, const int &b) {
        int sizea = a.size();
        Polynomial ret = a;
        ret.resize(sizea);
        for (int i = 0; i < sizea; ++i)ret[i] = (1ll * a[i] - b + mod) % mod;
        return ret;
    }
    inline Polynomial operator*(const Polynomial &a, const int &b) {
        int sizea = a.size();
        Polynomial ret = a;
        ret.resize(sizea);
        for (int i = 0; i < sizea; ++i) ret[i] = (1ll * a[i] * b % mod + mod) % mod;
        return ret;
    }
    inline Polynomial operator+(const Polynomial &a, const Polynomial &b) {
        int sizea = a.size(), sizeb = b.size(), size = max(sizea, sizeb);
        Polynomial ret = a;
        ret.resize(size);
        for (int i = 0; i < sizeb; ++i) ret[i] = (1ll * ret[i] + b[i]) % mod;
        return ret;
    }
    inline Polynomial operator-(const Polynomial &a, const Polynomial &b) {
        int sizea = a.size(), sizeb = b.size(), size = max(sizea, sizeb);
        Polynomial ret = a;
        ret.resize(size);
        for (int i = 0; i < sizeb; ++i) ret[i] = (1ll * ret[i] - b[i] + mod) % mod;
        return ret;
    }
    inline Polynomial Inverse(const Polynomial &a) {
        Polynomial ret, inv_a;
        ret.resize(1);
        ret[0] = Inv(a[0]);
        int ed = a.size();
        for (int len = 2; len <= ed; len <<= 1) {
            int n = Prepare_Transformation(len << 1);
            inv_a = a;
            inv_a.resize(n);
            ret.resize(n);
            for (int i = len; i < n; ++i) inv_a[i] = 0;
            NTT(inv_a, 1);
            NTT(ret, 1);
            for (int i = 0; i < n; ++i)
                ret[i] = 1ll * (2ll - 1ll * inv_a[i] * ret[i] % mod + mod) % mod * ret[i] % mod;
            NTT(ret, -1);
            for (int i = len; i < n; ++i) ret[i] = 0;
        }
        ret.resize(ed);
        return ret;
    }
    inline Polynomial operator*(const Polynomial &a, const Polynomial &b) {
        Polynomial lsa = a, lsb = b, ret;
        int n = lsa.size(), m = lsb.size();
        n = Prepare_Transformation(n + m);
        lsa.resize(n);
        lsb.resize(n);
        ret.resize(n);
        NTT(lsa, 1);
        NTT(lsb, 1);
        for (int i = 0; i < n; ++i) ret[i] = 1ll * lsa[i] * lsb[i] % mod;
        NTT(ret, -1);
        return ret;
    }
    inline Polynomial operator/(const Polynomial &a, const Polynomial &b) {
        Polynomial ret = a, ls = b;
        reverse(ret.begin(), ret.end());
        reverse(ls.begin(), ls.end());
        ls.resize(Binary_Rounding(a.size() + b.size()));
        ls = Inverse(ls);
        ls.resize(a.size() + b.size());
        ret = ret * ls;
        ret.resize(a.size() - b.size() + 1);
        reverse(ret.begin(), ret.end());
        return ret;
    }
    inline Polynomial operator%(const Polynomial &a, const Polynomial &b) {
        Polynomial ret = a / b;
        ret = ret * b;
        ret.resize(a.size() + b.size());
        ret = a - ret;
        ret.resize(a.size() + b.size());
        return ret;
    }
    inline Polynomial Derivation(const Polynomial &a) {
        int size = a.size();
        Polynomial ret;
        ret.resize(size);
        for (int i = 1; i < size; ++i) ret[i - 1] = 1ll * i * a[i] % mod;
        ret[size - 1] = 0;
        return ret;
    }
    inline Polynomial Integral(const Polynomial &a) {
        int size = a.size();
        Polynomial ret;
        ret.resize(size);
        for (int i = 1; i < size; ++i) ret[i] = 1ll * Inv(i) * a[i - 1] % mod;
        ret[0] = 0;
        return ret;
    }
    inline Polynomial Composition_Inverse(const Polynomial &a) {
        int n = a.size();
        Polynomial ret, Cinv = a, Pow;
        Cinv.resize(n);
        ret.resize(n);
        Pow.resize(n);
        Pow[0] = 1;
        for (int i = 0; i < n - 1; ++i) Cinv[i] = Cinv[i + 1];
        Cinv[n - 1] = 0;
        Cinv = Inverse(Cinv);
        for (int i = 1; i < n; ++i) {
            Pow = Pow * Cinv;
            Pow.resize(n);
            ret[i] = 1ll * Pow[i - 1] * Inv(i) % mod;
        }
        return ret;
    }
    inline Polynomial Logarithmic(const Polynomial &a) {
        Polynomial ln_a = Derivation(a) * Inverse(a);
        ln_a.resize(a.size());
        return Integral(ln_a);
    }
    inline Polynomial Exponential(const Polynomial &a, int Constant = 1) {
        Polynomial ret, D;
        int ed = a.size();
        ret.resize(1);
        ret[0] = Constant;
        for (int len = 2; len <= ed; len <<= 1) {
            D = Logarithmic(ret);
            D.resize(len);
            D[0] = (1ll * a[0] + 1ll - D[0] + mod) % mod;
            for (int i = 1; i < len; ++i) D[i] = (1ll * a[i] - D[i] + mod) % mod;
            int n = Prepare_Transformation(len << 1);
            ret.resize(n);
            D.resize(n);
            NTT(ret, 1);
            NTT(D, 1);
            for (int i = 0; i < n; ++i) ret[i] = 1ll * ret[i] * D[i] % mod;
            NTT(ret, -1);
            for (int i = len; i < (len << 1); ++i) ret[i] = D[i] = 0;
        }
        ret.resize(ed);
        return ret;
    }
}
using namespace NTT_;
//int dtol[100010], ltod[100010];
//bool check(int gg, int x) {
//    int tmp[8005] = { 0 };
//    for(int i = 0, tep = 1; i < x - 1; ++ i, tep = (ll)tep * gg % x) {
//        tmp[tep] ++;
//        if(tmp[tep] > 1) return false;
//    }
//    return true;
//}
//
//void get_G(int x) {
//    int GGG;
//    for(int i = 2; i < x; ++ i) {
//        if(check(i, x)){
//            GGG = i; break;
//        }
//    }
//    for(int i = 0, tep = 1; i < x - 1; ++ i, tep = (ll)tep * GGG % x) {
//        dtol[tep] = i; ltod[i] = tep;
//    }
//}

void solve() {
    int n; cin >> n;
    Polynomial a(n + 1); for(int i = 0; i < n; ++ i) cin >> a[i];
    // 2^0 2^1 2^2 ... 2^{n-1}
    ll ans = 0, res = 0;
    for(int i = 0; i < n; ++ i) {
        if(res) {
            int x = min(res, a[i] / 2);
            ans += x;
            a[i] -= x * 2;
            res -= x;
            ans += a[i] / 3;
            res += a[i] % 3;
        } else {
            ans += a[i] / 3;
            res += a[i] % 3;
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef ACM_LOCAL
    freopen("input", "r", stdin);
//    freopen("output", "w", stdout);
    signed test_index_for_debug = 1;
    char acm_local_for_debug = 0;
    do {
        if (acm_local_for_debug == '$') exit(0);
        if (test_index_for_debug > 20)
            throw runtime_error("Check the stdin!!!");
        auto start_clock_for_debug = clock();
        solve();
        auto end_clock_for_debug = clock();
        cout << "Test " << test_index_for_debug << " successful!" << endl;
        cerr << "Test " << test_index_for_debug++ << " Run Time: "
             << double(end_clock_for_debug - start_clock_for_debug) / CLOCKS_PER_SEC << "s" << endl;
        cout << "--------------------------------------------------" << endl;
    } while (cin >> acm_local_for_debug && cin.putback(acm_local_for_debug));
#else
    solve();
#endif
    return 0;
}