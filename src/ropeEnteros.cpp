#include <vector>
#include <iostream>
#include <cassert>

#define fst first
#define snd second
#define izq(n) (2*n+1)
#define der(n) (2*n+2)

using namespace std;

typedef pair<int,int> Interval;
Interval eInterval = {0,0};



int interval_len(Interval i)
{
    return i.snd - i.fst;
}

Interval interval_meet(Interval i, Interval j)
{
    int a = i.fst,b=i.snd,c=j.fst,d=j.snd;

    if(a<=c && d<=b)
        return {c,d};
    if(c<=a && b<=d)
        return {a,b};
    if(a<=c && b<=d)
        return {c,b};
    if(c<=a && d<=b)
        return {a,d};
    return eInterval;
}

bool interval_subset(Interval i, Interval j)
{
    return interval_meet(i,j)==i;
}

struct Rope {
    vector<int> v;
    int N;

    Rope(int n) {
        v.resize(4*n);
        N=n;
    }

    int query(int l, int r)
    {
        return query(l,r,0,0,N);
    }
    void update(int i, int x) { update_impl(0,0,N,i,x); }

    int query(int l, int r, int i, int lp, int rp) {
        if(r<=l)
            return 0;
        if(interval_subset({lp,rp},{l,r}))
            return v[i];

        int mid = (lp+rp)/2;
        
        Interval ml = interval_meet({l,r}, {lp,mid});
        Interval mr = interval_meet({l,r}, {mid, rp});
        return query(ml.first,ml.second, izq(i), lp, mid) + query(mr.first,mr.second, der(i), mid, rp);
    }

    void update_impl(int nodo, int l_, int r_, int i, int x) {
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