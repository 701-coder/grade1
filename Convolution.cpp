#include <bits/stdc++.h>
//#define int long long
#define LL long long
#define ll long long
using namespace std;
const int mod=998244353;

//(2^16)+1, 65537, 3
//7*17*(2^23)+1, 998244353, 3
//1255*(2^20)+1, 1315962881, 3
//51*(2^25)+1, 1711276033, 29
template<int MAXN, ll P, ll RT> //MAXN must be 2^k
struct NTT{
    ll w[MAXN];
    ll mpow(ll a, ll n){ll ret=1; for(; n; n>>=1, a=a*a%P)if(n&1)ret=ret*a%P; return ret;}
    ll minv(ll a){return mpow(a, P-2);}
    NTT(){ll dw=mpow(RT, (P-1)/MAXN); w[0]=1; for(int i=1; i<MAXN; ++i)w[i]=w[i-1]*dw%P;}
    void bitrev(ll *a, int n){int i=0; for(int j=1; j<n-1; ++j){for(int k=n>>1; (i^=k)<k; k>>=1); if(j<i)swap(a[i], a[j]);}}
    void operator()(ll *a, int n, bool inv = false) { //0 <= a[i] < P
        bitrev(a, n);
        for(int L=2; L<=n; L<<=1){
            int dx=MAXN/L, dl=L>>1;
            for(int i=0; i<n; i+=L)for(int j=i, x=0; j<i+dl; ++j, x+=dx){
                ll tmp=a[j+dl]*w[x]%P;
                if((a[j+dl]=a[j]-tmp)<0)a[j+dl]+=P;
                if((a[j]+=tmp)>=P)a[j]-=P;
            }
        }
        if(inv){reverse(a+1, a+n); ll invn=minv(n); for(int i=0; i<n; ++i)a[i]=a[i]*invn%P;}
    }
};

#define fi(s, n) for (int i=(int)(s); i<(int)(n); ++i)
template<int MAXN, ll P, ll RT> // MAXN = 2^k
struct Poly:vector<ll>{ // coefficients in [0, P)
    using vector<ll>::vector;
    static NTT<MAXN, P, RT> ntt;
    int n()const{return (int)size();} // n() >= 1
    Poly(const Poly &p, int _n):vector<LL>(_n){copy_n(p.data(), min(p.n(), _n), data());}
    Poly& irev(){return reverse(data(), data()+n()), *this;}
    Poly& isz(int _n){return resize(_n), *this;}
    Poly& iadd(const Poly &rhs){fi(0, n())if(((*this)[i]+=rhs[i])>=P)(*this)[i]-=P; return *this;}
    Poly& imul(ll k){fi(0, n())(*this)[i]=(*this)[i]*k%P; return *this;}
    Poly Mul(const Poly &rhs)const{
        int _n=1; while(_n<n()+rhs.n()-1)_n<<=1;
        Poly X(*this, _n), Y(rhs, _n);
        ntt(X.data(), _n), ntt(Y.data(), _n);
        fi(0, _n)X[i]=X[i]*Y[i]%P;
        ntt(X.data(), _n, true);
        return X.isz(n()+rhs.n()-1);
    }
    Poly Inv()const{ // (*this)[0] != 0
        if (n() == 1) return {ntt.minv((*this)[0])};
        int _n = 1;
        while (_n < n() * 2) _n <<= 1;
        Poly Xi = Poly(*this, (n() + 1) / 2).Inv().isz(_n);
        Poly Y(*this, _n);
        ntt(Xi.data(), _n), ntt(Y.data(), _n);
        fi(0, _n) {
            Xi[i] *= (2 - Xi[i] * Y[i]) % P;
            if ((Xi[i] %= P) < 0) Xi[i] += P;
        }
        ntt(Xi.data(), _n, true);
        return Xi.isz(n());
    }
    Poly Sqrt() const { // Jacobi((*this)[0], P) = 1
        if (n() == 1) return {QuadraticResidue((*this)[0], P)};
        Poly X = Poly(*this, (n() + 1) / 2).Sqrt().isz(n());
        return X.iadd(Mul(X.Inv()).isz(n())).imul(P / 2 + 1);
    }
    pair<Poly, Poly> DivMod(const Poly &rhs) const { // (rhs.)back() != 0
        if (n() < rhs.n()) return {{0}, *this};
        const int _n = n() - rhs.n() + 1;
        Poly X(rhs); X.irev().isz(_n);
        Poly Y(*this); Y.irev().isz(_n);
        Poly Q = Y.Mul(X.Inv()).isz(_n).irev();
        X = rhs.Mul(Q), Y = *this;
        fi(0, n()) if ((Y[i] -= X[i]) < 0) Y[i] += P;
        return {Q, Y.isz(max(1, rhs.n() - 1))};
    }
    Poly Dx()const{Poly ret(n()-1); fi(0, ret.n())ret[i]=(i+1)*(*this)[i+1]%P; return ret.isz(max(1, ret.n()));}
    Poly Sx()const{Poly ret(n()+1); fi(0, n())ret[i+1]=ntt.minv(i+1)*(*this)[i]%P; return ret;}
    Poly _tmul(int nn, const Poly &rhs) const {
        Poly Y = Mul(rhs).isz(n() + nn - 1);
        return Poly(Y.data() + n() - 1, Y.data() + Y.n());
    }
    vector<LL> _eval(const vector<LL> &x, const vector<Poly> &up) const {
        const int _n = (int)x.size();
        if (!_n) return {};
        vector<Poly> down(_n * 2);
        down[1] = DivMod(up[1]).second;
        fi(2, _n * 2) down[i] = down[i / 2].DivMod(up[i]).second;
        /* down[1] = Poly(up[1]).irev().isz(n()).Inv().irev()._tmul(_n, *this);
        fi(2, _n * 2) down[i] = up[i ^ 1]._tmul(up[i].n() - 1, down[i / 2]); */
        vector<LL> y(_n);
        fi(0, _n) y[i] = down[_n + i][0];
        return y;
    }
    static vector<Poly> _tree1(const vector<LL> &x) {
        const int _n = (int)x.size();
        vector<Poly> up(_n * 2);
        fi(0, _n) up[_n + i] = {(x[i] ? P - x[i] : 0), 1};
        for (int i = _n - 1; i > 0; --i) up[i] = up[i * 2].Mul(up[i * 2 + 1]);
        return up;
    }
    vector<LL> Eval(const vector<LL> &x) const {auto up = _tree1(x); return _eval(x, up);}
    static Poly Interpolate(const vector<LL> &x, const vector<LL> &y) {
        const int _n = (int)x.size();
        vector<Poly> up = _tree1(x), down(_n * 2);
        vector<LL> z = up[1].Dx()._eval(x, up);
        fi(0, _n) z[i] = y[i] * ntt.minv(z[i]) % P;
        fi(0, _n) down[_n + i] = {z[i]};
        for (int i = _n - 1; i > 0; --i) down[i] = down[i * 2].Mul(up[i * 2 + 1]).iadd(down[i * 2 + 1].Mul(up[i * 2]));
        return down[1];
    }
    Poly Ln()const{return Dx().Mul(Inv()).Sx().isz(n());}
    Poly Exp() const { // (*this)[0] == 0
        if (n() == 1) return {1};
        Poly X = Poly(*this, (n() + 1) / 2).Exp().isz(n());
        Poly Y = X.Ln(); Y[0] = P - 1;
        fi(0, n()) if ((Y[i] = (*this)[i] - Y[i]) < 0) Y[i] += P;
        return X.Mul(Y).isz(n());
    }
    Poly Pow(const string &K) const {
        int nz = 0;
        while (nz < n() && !(*this)[nz]) ++nz;
        LL nk = 0, nk2 = 0;
        for (char c : K) {
            nk = (nk * 10 + c - '0') % P;
            nk2 = nk2 * 10 + c - '0';
            if (nk2 * nz >= n()) return Poly(n());
            nk2 %= P - 1;
        }
        if (!nk && !nk2) return Poly(Poly {1}, n());
        Poly X(data() + nz, data() + nz + n() - nz * nk2);
        LL x0 = X[0];
        return X.imul(ntt.minv(x0)).Ln().imul(nk).Exp().imul(ntt.mpow(x0, nk2)).irev().isz(n()).irev();
    }
    static LL LinearRecursion(const vector<LL> &a, const vector<LL> &coef, LL n) { // a_n = \sum c_j a_(n-j)
        const int k = (int)a.size();
        assert((int)coef.size() == k + 1);
        Poly C(k + 1), W(Poly {1}, k), M = {0, 1};
        fi(1, k + 1) C[k - i] = coef[i] ? P - coef[i] : 0;
        C[k] = 1;
        while (n) {
            if (n % 2) W = W.Mul(M).DivMod(C).second;
            n /= 2, M = M.Mul(M).DivMod(C).second;
        }
        LL ret = 0;
        fi(0, k) ret = (ret + W[i] * a[i]) % P;
        return ret;
    }
};
#undef fi
using Poly_t = Poly<(1<<21), 998244353, 3>;
template<> decltype(Poly_t::ntt) Poly_t::ntt = {};

int n, m;
vector<int> a, b;
signed main(){
    ios::sync_with_stdio(0), cin.tie(0);
    cin>>n>>m;
    Poly_t a=Poly_t(n);
    Poly_t b=Poly_t(m);

    for(int i=0; i<n; ++i)cin>>a[i];
    for(int i=0; i<m; ++i)cin>>b[i];
    Poly_t c=a.Mul(b);
    for(int i=0; i<c.size(); ++i)cout<<c[i]<<' '; cout<<endl;
}
