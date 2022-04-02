#include <ctype.h>
#include <stdlib.h>
inline int getC(){
    static char buf[1<<21],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,(1<<20)+5,stdin),p1==p2)?EOF:*p1++;
}
int read(){
    register int ret=0,f=0;char ch=getC();
    while(!isdigit(ch)){if(ch==EOF)exit(0);if(ch=='-')f=1;ch=getC();}
    while(isdigit(ch)){ret=ret*10+ch-48;ch=getC();}
    return f?-ret:ret;
}
