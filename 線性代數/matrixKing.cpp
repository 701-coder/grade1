#include <bits/stdc++.h>
#define double long double
#define rep(i,n) for(int i=0; i<n; ++i)
#define kN 10
#define int long long
#define TEM template<typename T>
#define endl '\n'
using namespace std;

struct pq{
	int p=0, q=1;
	pq(){}
	pq(int _p, int _q):p(_p), q(_q){};
	pq(int _p):p(_p), q(1){};
	void Init(){if(q<0)q=-q, p=-p;}
	pq operator+(pq rhs)const{int d=__gcd(q, rhs.q), d1=q/d, d2=rhs.q/d, p1=p*d2+rhs.p*d1, q1=q*d2, d3=__gcd(p1, q1); return pq(p1/d3, q1/d3);}
	pq operator-()const{return q<0?pq(p, -q):pq(-p, q);}
	pq operator-(pq rhs)const{return *this+(-rhs);}
	pq operator*(pq rhs)const{int p1=p*rhs.p, q1=q*rhs.q, d=__gcd(p1, q1); return pq(p1/d, q1/d);}
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
	T1 a[kN][kN]={0}, g[kN][kN]={0}, gj[kN][kN]={0}, inv[kN][kN]={0}, q[kN][kN];
	bool freer[kN], freec[kN], invertible=1, gauss=0, gaussjordan=0, qr=0;
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
	void QR(){
		if(qr)return;

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
	Matrix<T1> Q(){

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
map<string, M_t> a;

signed main(){
	cout<<"This is a program to calculate some useful things of a matrix.\nIt may be helpful for your linear algebra homework.\n";
	string s;
	cout<<"Enter a command: ";
	while(cin>>s){
		if(s=="help")cout<<"\nInput a matrix:\n\
To input a m x n matrix, input m and n and m lines of n integers.\n\
Example:\n\
3 4\n\
1 2 3 4\n\
5 6 7 8\n\
9 0 1 2\n\n\
Functions:\n\
inv matrixName: return the inverse of matrixName\n\
T matrixName: return the transpose of matrixName\n\
N matrixName: return the null space of matrixName\n\
proj matrixName: return the projection of matrixName\n\
mul matrixName1 matrixName2: return matrixName1*matrixName2\n\n\
Commands:\n\
matrixName (or function): output the matrix (or result)\n\
new matrixName (input a matrix): let matrixName be the input matrix\n\
let matrixName1 functionName matrixName2: let matrixName1 be function(matrixName2)\n\
all matrixName: calculate the inverse, Gauss elimination, null space, Gauss elimination of transpose, left null space, projection of matrixName\n\
exit: end the program\n\n";
		else if(s=="new"){
			string t; cin>>t, a[t]=M_t(), cin>>a[t];
		}
		else if(s=="let"){
			string t, f, A; cin>>t>>f>>A;
			if(a.find(A)==a.end())cout<<"Matrix not found\n";
			else{
				if(f=="inv")a[t]=a[A].Inv();
				else if(f=="T")a[t]=a[A].T();
				else if(f=="N")a[t]=a[A].N();
				else if(f=="proj")a[t]=a[A].Proj();
				else if(f=="mul"){
					string B; cin>>B;
					if(a.find(B)==a.end())cout<<"Matrix not found\n";
					else a[t]=a[A]*a[B];
				}
				else cout<<"Function not found\n";
			}
		}
		else if(s=="inv"){string A; cin>>A, cout<<a[A].Inv();}
		else if(s=="T"){string A; cin>>A, cout<<a[A].T();}
		else if(s=="N"){string A; cin>>A, cout<<a[A].N();}
		else if(s=="proj"){string A; cin>>A, cout<<a[A].Proj();}
		else if(s=="mul"){
			string A, B; cin>>A>>B;
			if(a.find(A)==a.end()||a.find(B)==a.end())cout<<"Matrix not found\n";
			else cout<<a[A]*a[B];
		}
		else if(s=="all"){
			string t; cin>>t;
			M_t A=a[t], B; A.Gauss(), B=A.T(), B.Gauss(), A.GaussJordan(), B.GaussJordan();
			M_t G=M_t(A.m, A.n, A.g), H=M_t(B.m, B.n, B.g), G2=M_t(A.m, A.n, A.gj), H2=M_t(B.m, B.n, B.gj);
			cout<<"Inverse:\n"<<A.Inv()<<"Gauss elimination:\n"<<G;
			cout<<"Null space:\n"<<A.N();
			//for(int i=0; i<A.rk; ++i)cout<<A.pivot[i].first<<' '<<A.pivot[i].second<<endl;
			cout<<"Gauss elimination of transpose:\n"<<H;
			cout<<"Left null space:\n"<<B.N();
			cout<<"Projection:\n"<<A.Proj();
		}
		else if(s=="exit")return 0;
		else if(a.find(s)!=a.end())cout<<a[s];
		else cout<<"Not a command, enter \"help\" for more information\n";
		cout<<"Enter a command: ";
	}
}
