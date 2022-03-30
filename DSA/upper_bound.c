int upper_bound(ll *l, ll *r, ll x){ //the least i s.t. l[i]>x
    if(x<*l)return 0;
    ll *a=l;
    while(r-l>1){
        ll *m=l+(r-l>>1);
        if(*m>x)r=m;
        else l=m;
    }
    return l-a+1;
}
