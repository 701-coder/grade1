ll kth(ll *l, ll *r, int K){
    if(r-l<2)return *l;
    ll m=l[rand()%(r-l)];
    int i=0, j=0;
    for(int k=0; k<r-l; ++k){
        if(l[k]<m){
            if(k!=j)swap(l+i, l+j);
            swap(l+k, l+i), ++i, ++j;
        }
        else if(l[k]==m)swap(l+j, l+k), ++j;
    }
    return i<=K&&K<j?m:i>K?kth(l, l+i, K):kth(l+j, r, K-j);
}
