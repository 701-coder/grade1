#include <bits/stdc++.h>
#define double long double
#define rep(i,n) for(int i=0; i<n; ++i)
#define kN 10
#define int long long
#define TEM template<typename T>
#define endl '\n'
using namespace std;

int gcd(int a, int b){
	if(a<0)a=-a; if(b<0)b=-b;
	return a&&b?a>b?gcd(a%b, b):gcd(a, b%a):a+b;
}

struct pq{
	int p=0, q=1;
	pq(){}
	pq(int _p, int _q):p(_p), q(_q){};
	pq(int _p):p(_p), q(1){};
	void Init(){if(q<0)q=-q, p=-p;}
	pq operator+(pq rhs)const{int d=gcd(q, rhs.q), d1=q/d, d2=rhs.q/d, p1=p*d2+rhs.p*d1, q1=q*d2, d3=gcd(p1, q1); return pq(p1/d3, q1/d3);}
	pq operator-()const{return q<0?pq(p, -q):pq(-p, q);}
	pq operator-(pq rhs)const{return *this+(-rhs);}
	pq operator*(pq rhs)const{int p1=p*rhs.p, q1=q*rhs.q, d=gcd(p1, q1); return pq(p1/d, q1/d);}
	pq operator/(pq rhs)const{return *this*pq(rhs.q, rhs.p);}
	TEM pq operator+(T rhs)const{return *this+pq(rhs);}
	TEM pq operator-(T rhs)const{return *this-pq(rhs);}
	TEM pq operator*(T rhs)const{return *this*pq(rhs);}
	TEM pq operator/(T rhs)const{return *this/pq(rhs);}
	TEM void operator+=(T rhs){*this=*this+rhs;}
	TEM void operator-=(T rhs){*this=*this-rhs;}
	TEM void operator*=(T rhs){*this=*this*rhs;}
	TEM void operator/=(T rhs){*this=*this/rhs;}
	TEM void operator=(T rhs){*this=pq(rhs);}
	bool operator<(pq rhs){Init(), rhs.Init(); return rhs.q*p<q*rhs.p;}
	bool operator==(pq rhs)const{return p*rhs.q==q*rhs.p;}
	TEM bool operator<(T rhs){return *this<pq(rhs);}
	TEM bool operator>(T rhs){return pq(rhs)<*this;}
	TEM bool operator==(T rhs){return *this==pq(rhs);}
	TEM bool operator!=(T rhs)const{return !(*this==rhs);}
	TEM bool operator<=(T rhs){return !(rhs<*this);}
	TEM bool operator>=(T rhs){return !(*this<rhs);}

};

istream &operator>>(istream &in, pq &a){
	return a.q=1, in>>a.p;
}
ostream &operator<<(ostream &out, pq a){
	a.Init();
	return a.q==1?out<<a.p:out<<a.p<<'/'<<a.q;
}

template <typename T1>
struct Matrix{
	int m=0, n=0, rk=0;
	T1 a[kN][kN]={0}, g[kN][kN]={0}, gj[kN][kN]={0}, inv[kN][kN]={0};
	bool freer[kN], freec[kN], invertible=1, gauss=0, gaussjordan=0;
	pair<int, int> pivot[kN];
	Matrix(){}
	Matrix(int m, int n):m(m), n(n){}
	Matrix(int m, int n, T1 b[][kN]):m(m), n(n){
		rep(i, m)rep(j, n)a[i][j]=b[i][j];
	}
	void Gauss(){
		if(gauss)return;
		gauss=1;
		rep(i, m)rep(j, n)g[i][j]=a[i][j];
		rep(i, m)freer[i]=1;
		rep(l, n){
			int k=0;
			for(; k<m; ++k)if(g[k][l]!=0&&freer[k]){
				freer[k]=0;
				rep(i, m)if(freer[i]){
					T1 r=g[i][l]/g[k][l];
					rep(j, n)g[i][j]-=g[k][j]*r;
					g[i][l]=0;
				}
				break;
			}
		}
	}
	void GaussJordan(){
		if(gaussjordan)return;
		gaussjordan=1;
		if(m!=n)invertible=0;
		rep(i, m)rep(j, n)gj[i][j]=a[i][j], inv[i][j]=0;
		rep(i, m)freer[i]=1;
		rep(j, n)freec[j]=0;
		rep(i, min(m, n))inv[i][i]=1;
		rep(l, n){
			int k=0;
			for(; k<m; ++k)if(gj[k][l]!=0&&freer[k]){
				freer[k]=0;
				rep(i, m)if(i!=k){
					T1 r=gj[i][l]/gj[k][l];
					rep(j, n)gj[i][j]-=gj[k][j]*r, inv[i][j]-=inv[k][j]*r;
					gj[i][l]=0;
				}
				break;
			}
			if(k==m)invertible=0, freec[l]=1;
			else pivot[rk++]=make_pair(k, l);
		}
		rep(i, m){
			T1 r=0;
			rep(j, n)if(gj[i][j]!=0){r=(T1)1/gj[i][j]; rep(l, n)gj[i][l]*=r, inv[i][l]*=r; break;}
		}
	}
	Matrix<T1> Inv(){
		GaussJordan();
		Matrix<T1> M;
		if(!invertible)return M;
		M=Matrix(m, n);
		rep(i, m)rep(j, n)M.a[i][j]=inv[i][j];
		return M;
	}
	Matrix<T1> T(){
		Matrix<T1> M;
		M.m=n, M.n=m;
		rep(i, n)rep(j, m)M.a[i][j]=a[j][i];
		return M;
	}
	Matrix<T1> N(){
		GaussJordan();
		Matrix<T1> M=Matrix<T1>(n-rk, n);
		rep(i, rk){
			int k=0;
			rep(j, n)if(freec[j])M.a[k][pivot[i].second]=-gj[pivot[i].first][j], ++k;
		}
		int k=0;
		rep(j, n)if(freec[j])M.a[k][j]=1, ++k;
		return M;
	}
	Matrix<T1> operator*(Matrix<T1> r){
		Matrix<T1> M;
		if(n!=r.m)return M;
		M=Matrix<T1>(m, r.n);
		rep(i, m)rep(j, r.n){
			M.a[i][j]=0;
			rep(k, n)M.a[i][j]+=a[i][k]*r.a[k][j];
		}
		return M;
	}
	Matrix<T1> Proj(){
		return *this*(this->T()**this).Inv()*this->T();
	}
};

TEM istream &operator>>(istream &in, Matrix<T> &M){
	in>>M.m>>M.n;
	rep(i, M.m)rep(j, M.n)in>>M.a[i][j];
	return in;
}
TEM ostream &operator<<(ostream &out, Matrix<T> M){
	rep(i, M.m)rep(j, M.n)out<<M.a[i][j]<<"\t\n"[j==M.n-1];
	return out<<endl;
}

typedef Matrix<pq> M_t;

signed main(){
	cout<<"This is a program to calculate some useful things of a matrix.\nIt may be helpful for your linear algebra homework.\n";
	string s;
	cout<<"Enter a command: ";
	while(cin>>s){
		if(s=="help")cout<<"To input a m x n matrix, input m and n and m lines of n integers.\n\
Example:\n\
3 4\n\
1 2 3 4\n\
5 6 7 8\n\
9 0 1 2\n\
mul A B: calculate A*B\n\
all A: calculate the inverse, Gauss elimination, null space, Gauss elimination of transpose, left null space, projection of A\n\
exit: end the program\n";
		else if(s=="mul"){
			M_t A, B; cin>>A>>B;
			cout<<A*B;
		}
		else if(s=="all"){
			M_t A, B; cin>>A, A.Gauss(), B=A.T(), B.Gauss(), A.GaussJordan(), B.GaussJordan();
			M_t G=M_t(A.m, A.n, A.g), H=M_t(B.m, B.n, B.g), G2=M_t(A.m, A.n, A.gj), H2=M_t(B.m, B.n, B.gj);
			cout<<"Inverse:\n"<<A.Inv()<<"Gauss elimination:\n"<<G;
			cout<<"Null space:\n"<<A.N();
			//for(int i=0; i<A.rk; ++i)cout<<A.pivot[i].first<<' '<<A.pivot[i].second<<endl;
			cout<<"Gauss elimination of transpose:\n"<<H;
			cout<<"Left null space:\n"<<B.N();
			cout<<"Projection:\n"<<A.Proj();
		}
		else if(s=="exit")return 0;
		else cout<<"Not a command, enter \"help\" for more information\n";
		cout<<"Enter a command: ";
	}
}
