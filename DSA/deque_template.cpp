#include <bits/stdc++.h>
#define int long long
#define tem template<typename T>
using namespace std;
const int maxn=500000;
tem class dq{
	T *F, *E;
	int Size(){return E-F;}
	int pow2(int x){int r=1; for(; r<x; r<<=1); return r;}
	void RESIZE(int y){
		T *nF=new T[y];
		int z=size(), j=y-z>>1;
		for(int i=0; i<z; ++i, ++j)*(nF+j)=*(f+i);
		delete[] F;
		F=nF, E=F+y, e=F+j, f=e-z;
	}
	void Resize(){RESIZE(Size()<<1);}
	public:
	T *f, *e;
	void resize(int x){RESIZE(pow2(x<<1));}
	dq(int x){int y=pow2(x); F=new T[y<<1], E=F+(y<<1), f=e=F+y;}
	void push(T x){if(e==E)Resize(); *(e++)=x;}
	void push_front(T x){if(f==F)Resize(); *--f=x;}
	void pop(){--e;}
	void pop_front(){++f;}
	void clear(){delete[] F; F=new T[1], E=F+1, f=e=F;}
	int size(){return e-f;}
	T operator[](int x){return x>=0?*(f+x):*(e+x);}
};

int32_t main(){
	int n;
	while(cin>>n){
		dq<int> a=dq<int>(1);
		clock_t t=clock();
		for(int i=0; i<n; ++i)a.push(1);
		for(int i=0; i<n; ++i)a.push_front(1);
		cout<<clock()-t<<' ';
		t=clock();
		for(int i=0; i<n; ++i)a[i];
		cout<<clock()-t<<' ';
		a.clear();
		deque<int> b;
		t=clock();
		for(int i=0; i<n; ++i)b.push_back(1);
		for(int i=0; i<n; ++i)b.push_front(1);
		cout<<clock()-t<<' ';
		t=clock();
		for(int i=0; i<n; ++i)b[i];
		cout<<clock()-t<<endl;
		b.clear();
	}
	return 0;
}
