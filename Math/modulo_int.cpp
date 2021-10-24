#include <bits/stdc++.h>
#define monke_flip ios_base::sync_with_stdio(false); cin.tie(NULL);
#define random_monke srand(chrono::system_clock::now().time_since_epoch().count());
#ifdef LEL
#include <dbg.h>
#else
#define dbg(...) {/* temon kichu na; */}
#endif

using namespace std;
using LL = long long;
const int MONKE = 0;
template <LL mod> struct INT_MOD {
    LL val;
    INT_MOD(LL val = 0): val(val >= 0 ? val % mod : val % mod + mod) {}

    INT_MOD operator + (INT_MOD rhs) const { return INT_MOD((val + rhs.val)); }
    INT_MOD operator - (INT_MOD rhs) const { return INT_MOD((val - rhs.val)); }
    INT_MOD operator * (INT_MOD rhs) const { return INT_MOD((val * rhs.val)); }
    INT_MOD operator / (INT_MOD rhs) const { return INT_MOD( binpow(rhs, mod - 2) * val);}

    void operator += (INT_MOD rhs) { *this = *this + rhs; }
    void operator -= (INT_MOD rhs) { *this = *this - rhs; }
    void operator *= (INT_MOD rhs) { *this = *this * rhs; }
    void operator /= (INT_MOD rhs) { *this = *this / rhs; }

    friend INT_MOD binpow (INT_MOD val, LL p) {
        INT_MOD ans = 1;
        for (; p > 0; p >>= 1, val *= val)
            if (p & 1) 
                ans = ans * val;
        return ans;
    }
    friend ostream& operator << (ostream& o, INT_MOD &a) {
        o << a.val;
        return o;
    }
    friend istream& operator >> (istream& o, INT_MOD &a) {
        o >> a.val;
        return o;
    }
    friend LL abs(INT_MOD a) {
        return abs(a.val);
    }
};
int main()
{
    monke_flip
    INT_MOD <1000000007> a;
    return MONKE;
}