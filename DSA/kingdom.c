#include <stdio.h>
#include <stdbool.h>
#define kN 1000006

int n, q, s, r, lca[kN];
bool path[kN]={0};

typedef struct Node{
    struct Node* nxt;
    int v;
}node;

node head[kN], buf[kN<<1], *now[kN]; int nb=0;

bool dfs0(int x, int p){
    //printf("%d ", x);
    bool ret=x==s;
    for(node *i=head[x].nxt; i; i=i->nxt)if(i->v!=p&&dfs0(i->v, x))ret=1;
    return path[x]=ret;
}

void dfs1(int x, int p){
    lca[x]=path[x]?x:lca[p];
    for(node *i=head[x].nxt; i; i=i->nxt)if(i->v!=p)dfs1(i->v, x);
}

int main(){
    scanf("%d%d%d%d", &n, &q, &s, &r), --s, --r;
    for(int i=0; i<n; ++i)now[i]=head+i, head[i].nxt=buf[i].nxt=NULL;
    for(int i=0; i<n-1; ++i){
        int a, b;
        scanf("%d%d", &a, &b), --a, --b;
        buf[nb].v=b, now[a]->nxt=buf+nb, now[a]=now[a]->nxt, ++nb;
        buf[nb].v=a, now[b]->nxt=buf+nb, now[b]=now[b]->nxt, ++nb;
    }
    dfs0(r, -1), dfs1(r, -1);
    //for(int i=0; i<n; ++i)printf("%d %d\n", path[i], lca[i]);
    while(q--){
        int c;
        scanf("%d", &c), --c;
        printf("%d\n", lca[c]+1);
    }
}
