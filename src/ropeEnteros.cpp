#include <vector>
#include <iostream>
#include <cassert>
#include "interval.cpp"

#define fst first
#define snd second
#define izq(n) (2*n+1)
#define der(n) (2*n+2)

using namespace std;

// Usamos long long porque minimiza el riesgo de overflow y por lo
// tanto permite que la operacion sea cerrada.
using ll = long long;

struct Rope {
    vector<ll> v;
    int N;

    Rope(int n) { v.resize(4*n); N=n; }

    ll query(int l, int r) { return query(l,r,0,0,N); }

    void update(int i, ll x) { update_impl(0,0,N,i,x); }

    // Realiza la consulta sobre el intervalo [l, r)
    ll query(int l, int r, int i, int lp, int rp) {
        if(r<=l)
            return 0;
        if(interval_subset({lp,rp},{l,r}))
            return v[i];

        Interval m = interval_meet({l,r},{lp,rp});        
        if(m == eInterval)
            return 0;

        int mid = (lp+rp)/2;

        Interval ml = interval_meet({l,r}, {lp,mid});
        Interval mr = interval_meet({l,r}, {mid, rp});
        return query(ml.first,ml.second, izq(i), lp, mid) + query(mr.first,mr.second, der(i), mid, rp);
    }

    // Realiza la acutalizacion del indice i
    void update_impl(int nodo, int l_, int r_, int i, ll x) {
        int l = i, r = i+1;
        if (l <= l_ && r_ <= r) { 
            v[nodo] = x; 
            return; 
        }
        if (r <= l_ || r_ <= l) return;
        int m_ = (l_ + r_) / 2;
        // obs: una sola de estas dos llamadas hace algo, la otra cae en el caso base trivial
        //inmediatamente
        update_impl(izq(nodo), l_, m_, i, x);
        update_impl(der(nodo), m_, r_, i, x);
        v[nodo] = v[izq(nodo)] + v[der(nodo)]; // actualizo de abajo hacia arriba
    }
};