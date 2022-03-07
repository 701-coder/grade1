#include <stdio.h>
#include <stdbool.h>
#define kN 257

typedef struct Num{
    int a[kN];
}num;

void input(num *n){
    char c[kN];
    scanf("%s", c);
    int i=0;
    for(; c[i]!='\0'; ++i);
    for(int j=0; j<i; ++j)n->a[j]=c[i-j-1]-48;
    for(int j=i; j<kN; ++j)n->a[j]=0;
}

void output(num *n){
    int i=kN-1;
    for(; i>=0&&n->a[i]==0; --i);
    for(; i>=0; --i)printf("%d", n->a[i]);
    printf("\n");
}

bool nonzero(num *n){
    for(int i=0; i<kN; ++i)if(n->a[i])return 1;
    return 0;
}

bool isEven(num *n){
    return !(n->a[0]&1);
}

bool larger(num *n, num *m){
    for(int i=kN-1; i>=0; --i){
        if(n->a[i]>m->a[i])return 1;
        else if(n->a[i]<m->a[i])return 0;
    }
    return 0;
}

void minus(num *n, num *m){
    bool t=0;
    for(int i=0; i<kN; ++i){
        n->a[i]-=m->a[i]+t;
        if(n->a[i]<0)n->a[i]+=10, t=1;
        else t=0;
    }
}

void time2(num *n){
    bool t=0;
    for(int i=0; i<kN; ++i){
        n->a[i]=(n->a[i]<<1)+t;
        if(n->a[i]>9)n->a[i]-=10, t=1;
        else t=0;
    }
}

void div2(num *n){
    bool t=0;
    for(int i=kN-1; i>=0; --i){
        if(n->a[i]&1)n->a[i]=t*10+n->a[i]>>1, t=1;
        else n->a[i]=t*10+n->a[i]>>1, t=0;
    }
}

num gcd(num *n, num *m){
    int ans=0;
    while(nonzero(n)&&nonzero(m)){
        if(isEven(n)&&isEven(m))++ans, div2(n), div2(m);
        else if(isEven(n))div2(n);
        else if(isEven(m))div2(m);
        if(larger(n, m)){
            num *tmp=n; n=m, m=tmp;
        }
        minus(m, n);
    }
    while(ans--)time2(n);
    return *n;
}

int main(){
    num n, m;
    input(&n), input(&m);
    num ans=gcd(&n, &m);
    output(&ans);
}
