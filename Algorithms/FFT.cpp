#include <bits/stdc++.h>
using namespace std;
using LL = long long;

/*....................................................................*/ 
/**
1. Whenever possible remove leading zeros.
2. Custom Complex class may slightly improve performance.
3. Use pairfft to do two ffts of real vectors at once, slightly less accurate
than doing two ffts, but faster by about 30%.
4. FFT accuracy depends on answer. x <= 5e14 (double), x <= 1e18(long double)
   where x = max(ans[i]) for FFT, and x = N*mod for anymod **/
const double PI = acos(-1.0L);
using CD = complex <double>;
int N;
vector<int> perm;
vector<CD> wp[2];

void precalculate(int n) {
    assert((n & (n - 1)) == 0);
    N = n;
    perm = vector<int> (N, 0);
    for (int k = 1; k < N; k <<= 1)
        for (int i = 0; i < k; i++)
            perm[i] <<= 1, perm[i + k] = 1 + perm[i];

    wp[0] = wp[1] = vector<CD>(N);
    for (int i = 0; i < N; i++) {
        wp[0][i] = CD(cos(2 * PI * i / N),  sin(2 * PI * i / N));
        wp[1][i] = CD(cos(2 * PI * i / N), -sin(2 * PI * i / N));
    }
}

void fft(vector<CD> &v, bool invert = false) {
    if (v.size() != perm.size())    precalculate(v.size());

    for (int i = 0; i < N; i++)
        if (i < perm[i])
            swap(v[i], v[perm[i]]);

    for (int len = 2; len <= N; len *= 2) {
        for (int i = 0, d = N / len; i < N; i += len) {
            for (int j = 0, idx = 0; j < len / 2; j++, idx += d) {
                CD x = v[i + j];
                CD y = wp[invert][idx] * v[i + j + len / 2];
                v[i + j] = x + y;
                v[i + j + len / 2] = x - y;
            }
        }
    }

    if (invert) {
        for (int i = 0; i < N; i++) v[i] /= N;
    }
}

void pairfft(vector<CD> &a, vector<CD> &b, bool invert = false) {
    int N = a.size();
    vector<CD> p(N);
    for (int i = 0; i < N; i++) p[i] = a[i] + b[i] * CD(0, 1);
    fft(p, invert);
    p.push_back(p[0]);

    for (int i = 0; i < N; i++) {
        if (invert) {
            a[i] = CD(p[i].real(), 0);
            b[i] = CD(p[i].imag(), 0);
        } else {
            a[i] = (p[i] + conj(p[N - i])) * CD(0.5, 0);
            b[i] = (p[i] - conj(p[N - i])) * CD(0, -0.5);
        }
    }
}

vector<LL> multiply(const vector<LL> &a, const vector<LL> &b) {
    int n = 1;
    while (n < a.size() + b.size())  n <<= 1;

    vector<CD> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n); fb.resize(n);

//        fft(fa); fft(fb);
    pairfft(fa, fb);
    for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i];
    fft(fa, true);

    vector<LL> ans(n);
    for (int i = 0; i < n; i++)     ans[i] = round(fa[i].real());
    return ans;
}
/*....................................................................*/ 

int main() {
    string s;
    int shift = 1000002;
    vector <LL> a(shift + shift), b(shift + shift);
    cin >> s;
    for(size_t i = 0; i < s.size(); i++) {
        if(s[i] == 'A') a[i + shift]++;
        else b[-i + shift]++;
    }
    auto M = multiply(a, b);
    for(size_t i = 1; i < s.size(); i++) {
        cout << M[i + shift + shift] << '\n';
    }
}
