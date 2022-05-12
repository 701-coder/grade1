#include <bits/stdc++.h>
#define int long long
#define TEM template<typename T>
#define endl '\n'
using namespace std;

int gcd(int a, int b){
    if(a<0)a=-a;
    if(b<0)b=-b;
    return a&&b?a>b?gcd(a%b, b):gcd(a, b%a):a+b;
}

struct pq{
    int p, q;
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
    bool operator==(pq rhs)const{return p==rhs.p&&q==rhs.q;}
    TEM bool operator<(T rhs){return *this<pq(rhs);}
    TEM bool operator>(T rhs){return pq(rhs)<*this;}
    TEM bool operator==(T rhs){return *this==pq(rhs);}
    TEM bool operator!=(T rhs)const{return !(*this==rhs);}
    TEM bool operator<=(T rhs){return !(rhs<*this);}
    TEM bool operator>=(T rhs){return !(*this<rhs);}
};

istream& operator>>(istream &in, pq &rhs){return in>>rhs.p>>rhs.q;}
ostream& operator<<(ostream &out, const pq rhs){return out<<rhs.p<<'/'<<rhs.q<<' ';}

signed main(){
    pq a, b, c, d, p, q, r; cin>>a.p>>b.p>>c.p>>d.p, a.q=b.q=c.q=d.q=1;
    p=(-a*a*3+b*8)/8, q=(a*a*a-a*b*4+c*8)/8, r=(-a*a*a*a*3+a*a*b*16-a*c*64+d*256)/256;
    cout<<"p="<<p<<"\nq="<<q<<"\nr="<<r<<endl;
    cout<<"h(x)=1 "<<-p*2<<p*p-r*4<<q*q<<endl;
    cout<<"D="<<p*p*p*p*r*16-p*p*p*q*q*4-p*p*r*r*128+p*q*q*r*144-q*q*q*q*27+r*r*r*256<<endl;
}
