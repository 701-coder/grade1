#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define int long long
#define rep(i,a,b) for(int i=a; i<b; ++i)
#define kN 1000006
char s[kN]; int n=0;

inline bool isNumber(char c){return c>47&&c<58;}

int cal(int a, char b, int c){
    if(b=='-')return a-c;
    else if(b=='*')return a*c;
    else if(b=='/')return a==0?0:a>0^c>0?a>0?(a-1)/c-1:(a+1)/c-1:a/c;
    else if(b=='%')return a%c;
    else return a+c;
}

int Cal(int l, int *r){
    int a=0, b=0, c=0, i=l; char op1=0, op2=0;
    if(s[i]=='-')op1='-', ++i;
    for(; i<n&&s[i]!=')'; ++i){
        if(isNumber(s[i]))c=c*10+(s[i]-48);
        else if(s[i]=='(')c=Cal(i+1, &i);
        else{
            b=cal(b, op2, c), c=op2=0;
            if(s[i]=='=')b=cal(a, op1, b), a=op1=0, printf("Print: %lld\n", b);
            else if(s[i]=='*'||s[i]=='/'||s[i]=='%')op2=s[i];
            else if(s[i]=='+'||s[i]=='-')a=cal(a, op1, b), b=0, op1=s[i];
        }
    }
    return *r=i, cal(a, op1, cal(b, op2, c));
}

signed main(){
    scanf("%s", s);
    while(s[n]!='\0')++n;
    int r;
    Cal(0, &r);
}
