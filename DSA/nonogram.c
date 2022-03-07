#include <stdio.h>
#include <stdbool.h>
#define kN 25

bool a[kN][kN]; int r[kN][kN], c[kN][kN], n, m;

bool isValid(int x){
    int b[kN];
    for(int i=0; i<kN; ++i)b[i]=0;
    for(int i=0; i<m; ++i){
        if(a[x][i])++b[b[0]+1];
        else if(b[b[0]+1])++b[0];
    }
    if(b[b[0]+1])++b[0];
    for(int i=0; i<kN; ++i)if(r[x][i]!=b[i])return 0;
    return 1;
}

bool allIsValid(){
    for(int y=0; y<m; ++y){
        int b[kN];
        for(int i=0; i<kN; ++i)b[i]=0;
        for(int i=0; i<n; ++i){
            if(a[i][y])++b[b[0]+1];
            else if(b[b[0]+1])++b[0];
        }
        if(b[b[0]+1])++b[0];
        for(int i=0; i<kN; ++i)if(c[y][i]!=b[i])return 0;
    }
    return 1;
}

bool solve(int x){
    if(x==n)return allIsValid();
    for(int i=0; i<(1<<m); ++i){
        for(int j=0; j<m; ++j)a[x][j]=i&(1<<j);
        if(isValid(x)&&solve(x+1))return 1;
    }
    return 0;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i=0; i<n; ++i)for(int j=0; j<m; ++j)a[i][j]=0;
    for(int i=0; i<kN; ++i)for(int j=0; j<kN; ++j)r[i][j]=c[i][j]=0;
    for(int i=0; i<n; ++i){
        scanf("%d", &r[i][0]);
        for(int j=1; j<=r[i][0]; ++j)scanf("%d", &r[i][j]);
    }
    for(int i=0; i<m; ++i){
        scanf("%d", &c[i][0]);
        for(int j=1; j<=c[i][0]; ++j)scanf("%d", &c[i][j]);
    }
    if(n==1){
        for(int i=0; i<m; ++i)printf("%c", c[i][0]?'o':'_');
        printf("\n");
        return 0;
    }
    solve(0);
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j)printf("%c", a[i][j]?'o':'_');
        printf("\n");
    }
    return 0;
}
