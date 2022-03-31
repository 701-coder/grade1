#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "price.h"
#define ll unsigned long long
#define kN 1050000
#define kM 1024
#define oo 1000000000
int a, q, n, s[kM], mn[kM];
ll b[kN*5], c[kM*4]; int nb=0;

int rand(){
    static unsigned x=1357997531;
    return (x=(x<<2)+x+1)>>3;
}

inline int min(int a, int b){return a<b?a:b;}
inline int max(int a, int b){return a>b?a:b;}
inline void swap(ll *a, ll *b){ll tmp=*a; *a=*b, *b=tmp;}
inline ll minl(ll a, ll b){return a<b?a:b;}

ll Price(int s, int t){return price(s, t+1);}

typedef struct T{
    int id, jd; ll p;
}T;

T t[kN]; int nt=0;

void sort(ll *l, ll *r){
    static ll buf[kN];
    if(r-l<2)return;
    ll *m=l+(r-l>>1);
    sort(l, m), sort(m, r);
    for(int i=0; i<r-l; ++i)buf[i]=l[i];
    ll *k=l;
    for(int i=0, j=m-l; k<r; ++k)*k=j==r-l||i<m-l&&buf[i]<buf[j]?buf[i++]:buf[j++];
}

void sorti(int *l, int *r){
    static int buf[kN];
    if(r-l<2)return;
    int *m=l+(r-l>>1);
    sorti(l, m), sorti(m, r);
    for(int i=0; i<r-l; ++i)buf[i]=l[i];
    int *k=l;
    for(int i=0, j=m-l; k<r; ++k)*k=j==r-l||i<m-l&&buf[i]<buf[j]?buf[i++]:buf[j++];
}

void sortt(T *l, T *r){
    static T buf[kN];
    if(r-l<2)return;
    T *m=l+(r-l>>1);
    sortt(l, m), sortt(m, r);
    for(int i=0; i<r-l; ++i)buf[i]=l[i];
    T *k=l;
    for(int i=0, j=m-l; k<r; ++k)*k=j==r-l||i<m-l&&buf[i].p<buf[j].p?buf[i++]:buf[j++];
}

int upper_bound(ll *l, ll *r, ll x){ //the least i s.t. l[i]>x
    if(x<*l)return 0;
    ll *a=l;
    while(r-l>1){
        ll *m=l+(r-l>>1);
        if(*m>x)r=m;
        else l=m;
    }
    return l-a+1;
}

ll kth(ll *l, ll *r, int K){
    if(r-l<2)return *l;
    ll m=l[rand()%(r-l)];
    int i=0, j=0;
    for(int k=0; k<r-l; ++k){
        if(l[k]<m){
            if(k!=j)swap(l+i, l+j);
            swap(l+k, l+i), ++i, ++j;
        }
        else if(l[k]==m)swap(l+j, l+k), ++j;
    }
    return i<=K&&K<j?m:i>K?kth(l, l+i, K):kth(l+j, r, K-j);
}

int main(){
    scanf("%d%d%d", &a, &q, &n);
    for(int i=0; i<a; ++i)scanf("%d", &s[i]);
    sorti(s, s+a);
    for(int i=0; i<a; ++i)for(int j=2; j<kM; ++j)t[nt].id=i, t[nt].jd=j, t[nt].p=Price(s[i], j<<10), ++nt;
    sortt(t, t+nt);
    for(int i=0; i<a; ++i)mn[i]=1;
    for(int i=0; i<kM; ++i)mn[t[i].id]=max(mn[t[i].id], t[i].jd+1);
    for(int i=0; i<a; ++i)for(int j=0; j<min((mn[i]+2<<10), oo+1); ++j)b[nb++]=Price(s[i], j), assert(nb<(kN*5));
    ll ub=kth(b, b+nb, 999999);
    for(int i=0, j=0; i<nb; ++i)if(b[i]<=ub)b[j++]=b[i];
    nb=1000000, sort(b, b+nb);
    while(q--){
        int s0, k;
        scanf("%d%d", &s0, &k), --k;
        int l=0, r=a;
        while(r-l>1){
            int m=l+r>>1;
            if(s[m]>s0)r=m;
            else l=m;
        }
        ll Mn=Price(s0, 0);
        for(int i=1; i<=kM; ++i)Mn=minl(Mn, Price(s0, i));
        if(s0==s[l]||s0==0||Mn>=b[k]){printf("%llu\n", b[k]); continue;}
        l=1, r=kM<<1;
        while(r-l>1){
            int m=l+r>>1;
            if(upper_bound(b, b+nb, Price(s0, m<<10))+(m-1<<10)>k)r=m;
            else l=m;
        }
        int L=max(l-2, 0);
        for(int i=0; i<kM*4; ++i)c[i]=Price(s0, (L<<10)+i);
        sort(c, c+kM*4), k-=L<<10;
        l=0, r=kM*4;
        while(r-l>1){
            int m=l+r>>1;
            if(upper_bound(b, b+nb, c[m])+m>k)r=m;
            else l=m;
        }
        int x=upper_bound(b, b+nb, c[l])+l;
        printf("%llu\n", x==k?c[l]:b[k-l-1]);
    }
}
