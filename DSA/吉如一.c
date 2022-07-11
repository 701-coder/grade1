#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#define kN 100005
#define oo 1000000007
#define int long long
#define print fflush(stdout)

inline int max(int a, int b){return a>b?a:b;}
inline int min(int a, int b){return a<b?a:b;}
inline void swap(int *a, int *b){int tmp=*a; *a=*b, *b=tmp;}

typedef struct treap{
    int v, mx, nmx, smx, nsmx, sm, sz, hp, k;
    bool rev;
    struct treap *l, *r;
}treap;

typedef struct ptreap{
    treap *x, *y;
}ptreap;

treap buf[kN<<1]; int nbuf=0, N, Q;

void push(treap *x){
    if(!x)return;
    if(x->rev){
        treap *tmp=x->l; x->l=x->r, x->r=tmp, x->rev=0;
        if(x->l)x->l->rev^=1;
        if(x->r)x->r->rev^=1;
    }
    if(x->k<oo){
        assert(x->k>x->smx);
        if(x->smx<x->k&&x->k<x->mx){
            x->sm-=(x->mx-x->k)*x->nmx, x->v=min(x->v, x->k), x->mx=x->k;
            if(x->l)x->l->k=min(x->l->k, x->k);
            if(x->r)x->r->k=min(x->r->k, x->k);
        }
        x->k=oo;
    }
}

void pull(treap *x){
    if(!x)return;
    int a[5], b[5], mx=0, smx=0; a[0]=x->v, b[0]=1, x->sz=1, x->sm=x->v;
    if(x->l)push(x->l), a[1]=x->l->mx, a[2]=x->l->smx, b[1]=x->l->nmx, b[2]=x->l->nsmx, x->sz+=x->l->sz, x->sm+=x->l->sm;
    else a[1]=a[2]=-oo, b[1]=b[2]=0;
    if(x->r)push(x->r), a[3]=x->r->mx, a[4]=x->r->smx, b[3]=x->r->nmx, b[4]=x->r->nsmx, x->sz+=x->r->sz, x->sm+=x->r->sm;
    else a[3]=a[4]=-oo, b[3]=b[4]=0;
    for(int i=1; i<5; ++i)if(a[mx]<a[i])mx=i;
    for(int i=1; i<5; ++i)if(a[smx]==a[mx]||a[smx]<a[i]&&a[i]<a[mx])smx=i;
    x->mx=a[mx], x->smx=a[smx], x->nmx=x->nsmx=0;
    for(int i=0; i<5; ++i){
        if(a[i]==a[mx])x->nmx+=b[i];
        if(a[i]==a[smx])x->nsmx+=b[i];
    }
}

treap *init(int v){
    treap *x=buf+nbuf++;
    x->v=x->mx=x->sm=v, x->smx=-oo, x->nmx=1, x->nsmx=0, x->sz=1, x->hp=rand(), x->k=oo, x->rev=0, x->l=x->r=NULL;
    return x;
}

treap *merge(treap *x, treap *y){
    //printf("%p %p\n", x, y);
    if(!x)return y;
    if(!y)return x;
    //printf("%lld %lld\n", x->v, y->v);
    if(x->hp>y->hp)return push(x), x->r=merge(x->r, y), pull(x), x;
    return push(y), y->l=merge(x, y->l), pull(y), y;
}

ptreap split(treap *x, int id){ // the size of the left subtree is id
    push(x);
    ptreap ret;
    if(id==0||!x){ret.x=NULL, ret.y=x; return ret;}
    int lsz=x->l?x->l->sz:0;
    if(id==x->sz)ret.x=x, ret.y=NULL;
    else if(id<=lsz){
        ptreap p=split(x->l, id);
        x->l=p.y, ret.x=p.x, ret.y=x;
    }
    else{
        ptreap p=split(x->r, id-lsz-1);
        x->r=p.x, ret.x=x, ret.y=p.y;
    }
    pull(x);
    return ret;
}

void tok(treap *x, int l, int r, int k){
    if(!x)return;
    push(x);
    int lsz=x->l?x->l->sz:0;
    if(k>=x->mx)return;
    if(l<=lsz&&lsz<r&&x->v>k)x->v=k;
    if(l<=0&&x->sz<=r){
        if(k<=x->smx)tok(x->l, l, r, k), tok(x->r, l-lsz-1, r-lsz-1, k), pull(x);
        else x->k=k, push(x);
        return;
    }
    if(l<lsz)tok(x->l, l, r, k);
    if(r>lsz+1)tok(x->r, l-lsz-1, r-lsz-1, k);
    pull(x);
}

int query(treap *x, int l, int r){
    if(!x)return 0;
    push(x);
    int lsz=x->l?x->l->sz:0;
    if(l<=0&&x->sz<=r)return x->sm;
    int sm=0;
    if(l<=lsz&&lsz<r)sm+=x->v;
    if(l<lsz)sm+=query(x->l, l, r);
    if(r>lsz+1)sm+=query(x->r, l-lsz-1, r-lsz-1);
    return sm;
}

void output(treap *x){
    if(!x)return;
    push(x), output(x->l), printf("%lld ", x->v), output(x->r);
}

int toarr[kN];
void toarray(treap *x, int id){
    if(!x)return;
    int lsz=x->l?x->l->sz:0;
    push(x), toarray(x->l, id), toarr[id+lsz]=x->v, toarray(x->r, id+lsz+1);
}

signed main(){
    scanf("%lld%lld", &N, &Q);
    treap *root=NULL;
    for(int i=0; i<N; ++i){int a; scanf("%lld", &a), root=merge(root, init(a));}
    int T=0;
    while(Q--){
        //output(root), printf("\n"), fflush(stdout);
        int t; scanf("%lld", &t);
        //if(T>0)return 0;
        if(t==1){
            int p, k; scanf("%lld%lld", &p, &k);
            ptreap a=split(root, p); root=merge(merge(a.x, init(k)), a.y);
        }
        else if(t==2){
            int p; scanf("%lld", &p);
            ptreap a=split(root, p-1), b=split(a.y, 1); root=merge(a.x, b.y);
        }
        else if(t==3){
            int l, r; scanf("%lld%lld", &l, &r);
            ptreap a=split(root, l-1), b=split(a.y, r-l+1);
            push(b.x), b.x->rev=1, root=merge(merge(a.x, b.x), b.y);
            //printf("%p %p %p %p\n", root, a.x, b.x, b.y), print;
        }
        else if(t==4){
            int l1, r1, l2, r2; scanf("%lld%lld%lld%lld", &l1, &r1, &l2, &r2);
            if(l1>l2)swap(&l1, &l2), swap(&r1, &r2);
            ptreap a=split(root, l1-1), b=split(a.y, r1-l1+1), c=split(b.y, l2-r1-1), d=split(c.y, r2-l2+1);
            root=merge(merge(merge(merge(a.x, d.x), c.x), b.x), d.y);
        }
        else if(t==5){
            int l, r, k; scanf("%lld%lld%lld", &l, &r, &k);
            tok(root, l-1, r, k);
            //toarray(root, 0);
            //for(int i=l-1; i<r; ++i)assert(toarr[i]<=k);
        }
        else{
            int l, r; scanf("%lld%lld", &l, &r);
            ptreap a=split(root, l-1), b=split(a.y, r-l+1);
            push(b.x);
            printf("%lld\n", b.x->sm);
            root=merge(merge(a.x, b.x), b.y);
            //printf("%lld\n", query(root, l-1, r));
        }
        ++T;
    }
}
