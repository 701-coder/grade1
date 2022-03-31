void sort(ll *l, ll *r){
    static ll buf[kN];
    if(r-l<2)return;
    ll *m=l+(r-l>>1);
    sort(l, m), sort(m, r);
    for(int i=0; i<r-l; ++i)buf[i]=l[i];
    ll *k=l;
    for(int i=0, j=m-l; k<r; ++k)*k=j==r-l||i<m-l&&buf[i]<buf[j]?buf[i++]:buf[j++];
}
