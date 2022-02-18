#include <bits/stdc++.h>
using namespace std;

struct date{
    int y, m, d;
    string c, s;
    date(){}
    date(int y, int m, int d):y(y), m(m), d(d), c(""), s(""){}
    date(int y, int m, int d, string c, string s):y(y), m(m), d(d), c(c), s(s){}
    bool isLeap(){return !(y&3)&&(y%100||!(y%400));}
    int week(){
        if(m<3)m+=12, --y;
        int w=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
        if(m>12)m-=12, ++y;
        return w;
    }
    bool operator<(const date r)const{
        if(y<r.y)return 1;
        if(y>r.y)return 0;
        if(m<r.m)return 1;
        if(m>r.m)return 0;
        if(d<r.d)return 1;
        if(d>r.d)return 0;
        if(c<r.c)return 1;
        if(c>r.c)return 0;
        if(s<r.s)return 1;
        return 0;
    }
    bool eq(const date r)const{
        return y==r.y&&m==r.m&&d==r.d;
    }
    date operator++(){
        int month[13]={31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(isLeap())month[2]=29;
        ++d;
        if(d>month[m])d-=month[m++];
        if(m>12)m-=12, ++y;
        return *this;
    }
    date operator--(){
        int month[13]={31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(isLeap())month[2]=29;
        --d;
        if(d<1)d+=month[--m];
        if(m<1)m+=12, --y;
        return *this;
    }
    date operator+(int n){
        date r=*this;
        if(n>=0){while(n--)++r; return r;}
        while(n++)--r;
        return r;
    }
    date operator-(int n){return *this+(-n);}
}a[10000];

int n=0;

vector<date> v[10000];

int main(){
    ifstream in;
    in.open("schedule");
    int y=2021;
    while(1){
        int m, d; string c, s;
        if(!(in>>m))break;
        if(m>12){y=m; continue;}
        if(!(in>>d>>c>>s))break;
        a[n++]=date(y, m, d, c, s);
    }
    cout<<n<<" schedules selected...\nEnter your starting year and month: ";
    sort(a, a+n);
    int sy, sm;
    cin>>sy>>sm;
    date st=date(sy, sm, 1);
    while(st.week())--st;
    int si=lower_bound(a, a+n, st)-a, t=0;
    for(date i=st; i<a[n-1]; ++i, ++t)while(si<n&&i.eq(a[si]))v[t].push_back(a[si]), ++si;
    cout<<t<<endl;
    date di=st;
    const int wid=16;
    for(int j=0; j<wid*7+1; ++j)cout<<(j%wid?'_':' '); cout<<endl;
    for(int i=0; i<t;){
        int mx=0;
        for(int j=0; j<7; ++j)mx=max(mx, (int)v[i+j].size());
        for(int j=0; j<7; ++j, ++di){
            cout<<'|'<<di.m<<'/'<<di.d;
            if(di.m<10)cout<<' ';
            if(di.d<10)cout<<' ';
            for(int k=0; k<wid-6; ++k)cout<<' ';
        }
        cout<<"|\n";
        for(int sz=0; sz<mx; ++sz){
            for(int j=0; j<7; ++j){
                cout<<"| ";
                if(sz<v[i+j].size()){cout<<v[i+j][sz].c; for(int k=0; k<wid-2-v[i+j][sz].c.size(); ++k)cout<<' ';}
                else for(int k=0; k<wid-2; ++k)cout<<' ';
            }
            cout<<"|\n";
            for(int j=0; j<7; ++j){
                cout<<"|  ";
                if(sz<v[i+j].size()){cout<<v[i+j][sz].s; for(int k=0; k<wid-3-v[i+j][sz].s.size(); ++k)cout<<' ';}
                else for(int k=0; k<wid-3; ++k)cout<<' ';
            }
            cout<<"|\n";
        }
        for(int j=0; j<wid*7+1; ++j)cout<<(j%wid?'_':'|');
        cout<<endl;
        i+=7;
    }
}
