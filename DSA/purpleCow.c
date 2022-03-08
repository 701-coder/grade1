#include <stdio.h>
#include <stdbool.h>
#define kN 1000006


int m, k;
inline int idx(int a, int b){return a*k+b;}

typedef struct ll{
    struct ll *prv, *nxt;
    int gp, id;
}ll;
//the id of head and tail is the index of bathroom

ll *p[kN], *q[kN], head[kN], tail[kN], bth[kN];

void rev(ll *a){
    ll *b=a->prv;
    a->prv=a->nxt, a->nxt=b;
}

void insert(ll *a, ll c, int bth){
    ll *b=(ll*)malloc(sizeof(ll));
    *b=c;
    if(!a->nxt)a=a->prv;
    b->nxt=a->nxt, b->prv=a, a->nxt=a->nxt->prv=b, p[idx(bth, b->gp)]=b;
    if(b->gp!=a->gp)q[idx(bth, b->gp)]=b;
}

void delback(ll *a){
    if(a->prv->prv==a)rev(a->prv);
    a->nxt->prv=a->prv, a->prv->nxt=a->nxt;
    p[idx(a->nxt->id, a->gp)]=a->prv->gp==a->gp?a->prv:a->nxt;
    if(a->gp!=a->prv->gp)q[idx(a->nxt->id, a->gp)]=a->nxt;
}

void delfront(ll *a){
    if(a->nxt->nxt==a)rev(a->nxt);
    a->nxt->prv=a->prv, a->prv->nxt=a->nxt;
    if(a->nxt->gp!=a->gp)p[idx(a->prv->id, a->gp)]=q[idx(a->prv->id, a->gp)]=tail+a->prv->id;
    else q[idx(a->prv->id, a->gp)]=a->nxt;
}

void del(ll *a){
    a->prv->nxt=a->nxt, a->nxt->prv=a->prv;
}

void connect(ll *a, ll *l, ll *r, int bth){
    if(!a->nxt)a=a->prv;
    if(l==r)l->nxt=a->nxt, l->prv=a, a->nxt=a->nxt->prv=l;
    else a->nxt->prv=l, rev(l), l->nxt=a->nxt, a->nxt=r, rev(r), r->prv=a;
    p[idx(bth, l->gp)]=l;
    if(q[idx(bth, r->gp)]==tail+bth)q[idx(bth, r->gp)]=r;
}

void print(){
    for(int i=0; i<m; ++i){
        for(ll *now=head+i; now->nxt&&now!=tail+i; now=now->nxt){
            if(now->nxt->nxt==now)rev(now->nxt);
            if(now!=head+i)printf("%d ", now->id);
        }
        printf("\n");
    }
}

int main(){
    int n;
    scanf("%d%d%d", &m, &n, &k);
    for(int i=0; i<m; ++i){
        head[i].nxt=tail+i, tail[i].prv=head+i, head[i].prv=tail[i].nxt=NULL, head[i].id=tail[i].id=bth[i].id=i, head[i].gp=tail[i].gp=-1;
        for(int j=0; j<k; ++j)p[idx(i, j)]=q[idx(i, j)]=tail+i;
    }
    for(int i=0; i<m-1; ++i)bth[i].nxt=bth+i+1, bth[i+1].prv=bth+i; bth[0].prv=bth+m-1, bth[m-1].nxt=bth;
    while(n--){
        char cmd[10]; int a;
        scanf("%s%d", cmd, &a);
        if(cmd[0]=='e'){
            int b, c;
            scanf("%d%d", &b, &c);
            ll d;
            d.gp=a, d.id=b, insert(p[idx(c, a)], d, c);
        }
        else if(cmd[0]=='l')delback(tail[a].prv);
        else if(cmd[0]=='g')delfront(head[a].nxt);
        else{
            del(bth+a);
            static int gp[kN];
            int j=0;
            for(int now=tail[a].prv->gp; now!=-1; now=q[idx(a, now)]->prv->gp)gp[j++]=now;
            for(int i=0, now=gp[0]; i<j; now=gp[++i])connect(p[idx(bth[a].prv->id, now)], q[idx(a, now)], p[idx(a, now)], bth[a].prv->id);
            head[a].nxt=NULL;
        }
    }
    print();
}
