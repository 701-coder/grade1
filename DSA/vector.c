#include <stdlib.h>
int highbit(int n){int l=0, r=32; while(r-l>1){int m=l+r>>1; (1<<m)>n?(r=m):(l=m);} return 1<<l;}
typedef struct vec{ll *a; int sz, Sz;}vec;
void init(vec *v){v->Sz=1, v->sz=0, v->a=(ll*)malloc(v->Sz*sizeof(ll));}
void resize(vec *v, int n){v->Sz=highbit(n)<<1, v->a=(ll*)realloc(v->a, v->Sz*sizeof(ll));}
void push_back(vec *v, ll n){if(v->sz==v->Sz)resize(v, v->sz); v->a[v->sz++]=n;}
void pop_back(vec *v){if(v->sz<=(v->Sz>>2))resize(v, v->sz); --v->sz;}
