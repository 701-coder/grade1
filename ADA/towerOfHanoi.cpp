#include <bits/stdc++.h>
#define int long long
using namespace std;
const int p=998244353, kN=100005;
int a[kN], n;

int Pow(int a, int b){
	int c=1;
	for(; b; a=a*a%p, b>>=1)if(b&1)c=c*a%p;
	return c;
}

int solve(int m, int from, int to){
	if(m==-1)return 0;
	int ret=0;
	if(a[m]==to){
		int s=solve(m-1, 3-from-to, to);
		if(s==-1)return -1;
		ret=(ret+s)%p;
	}
	else if(a[m]==from){
		int s=solve(m-1, from, 3-to-from);
		if(s==-1)return -1;
		ret=(ret+s+Pow(2, m))%p;
	}
	else return -1;
	return ret;
}

signed main(){
	scanf("%lld", &n);
	for(int i=0; i<3; ++i){
		int m; scanf("%lld", &m);
		for(;m--;){
			int x; scanf("%lld", &x);
			a[x-1]=i;
		}
	}
	printf("%lld\n", solve(n-1, 0, 2));
}
