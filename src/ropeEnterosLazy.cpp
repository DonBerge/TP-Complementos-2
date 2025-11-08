#include <vector>
#include <iostream>
#include "interval.cpp"

#define izq(n) (2*n+1)
#define der(n) (2*n+2)


using ll = long long;

unsigned next_power_of_2(unsigned n)
{
    if(n==0)
        return 1;
    if((n & (n-1)) == 0)
        return n; // ya es potencia de 2
    unsigned msb = 0; // el bit mas significativo de n
    for(unsigned i=0;i<32;i++)
        if(n & (1<<i))
            msb = i;
    //cout<<"Most significant bit of "<<n<<" is bit "<<msb<<" the next power of 2 is therefore "<<(1<<(msb+1))<<endl;
    return 1<<(msb+1);
}

struct Rope {
    vector<ll> v;
    vector<ll> lazy;
    int N;

    Rope(int n) {
        unsigned sz = 2*next_power_of_2(n)+1;
        v.resize(sz);
        lazy.resize(sz);
        N=n;
    }

    ll query(int l, int r){ return query(l,r,0,0,N); }

    void update(int i, ll x) { update_rango(i,i+1,x); }

    void update_rango(int l, int r, ll x) { update_impl(0,0,N,l,r,x);}

    // Realiza la consulta sobre el intervalo [l, r)
    ll query(int l, int r, int i, int lp, int rp) {
        if(r<=l)
            return 0;

        propagate(i,lp,rp);
        
        if(interval_subset({lp,rp},{l,r}))
            return v[i];
        
        Interval m = interval_meet({l,r},{lp,rp});        
        if(m == eInterval)
            return 0;

        int mid = (lp+rp)/2;
        
        Interval ml = interval_meet(m, {lp,mid});
        Interval mr = interval_meet(m, {mid, rp});
        return query(ml.first,ml.second, izq(i), lp, mid) + query(mr.first,mr.second, der(i), mid, rp);
    }

    // Realiza la acutalizacion deL intervalo [l, r) con el valor upd
    void update_impl(int node, int l_, int r_, int l, int r, ll upd) {
        propagate(node, l_, r_);
        if (l <= l_ && r_ <= r) { lazy[node] = upd; propagate(node, l_, r_); return; }
        if (r <= l_ || r_ <= l) { return; }

        int m_ = (l_ + r_) / 2;

        update_impl(izq(node), l_, m_, l, r, upd);
        update_impl(der(node), m_, r_, l, r, upd);
        v[node] = v[izq(node)] + v[der(node)];
    }

    void propagate(int node, int l_, int r_) {
        int len = r_ - l_;
        if (len > 1) { // no es hoja, combino actualizaciones en los hijos
            lazy[izq(node)] = lazy[izq(node)] + lazy[node];
            lazy[der(node)] = lazy[der(node)] + lazy[node];
        }
        v[node] = v[node] + lazy[node] * len;
        lazy[node] = 0;
    }
};