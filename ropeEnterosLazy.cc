#include <vector>
#include <iostream>

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
    vector<int> lazy;
    int N;

    Rope(int n) {
        v.resize(2*n+1);
        lazy.resize(2*n+1);
        N=n;
    }

    int query(int l, int r)
    {
        return query(l,r,0,0,N);
    }
    void update(int i, int x) { update_rango(i,i+1,x); }
    void update_rango(int l, int r, int x) { update_impl(0,0,N,l,r,x);}

    int query(int l, int r, int i, int lp, int rp) {
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

    void update_impl(int node, int l_, int r_, int l, int r, int upd) {
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

int main() {
    int n;
    cin>>n;
    Rope rope(n);
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        rope.update(i, x);
    }
    rope.update_rango(0,n,10);
    int l,r;
    cin>>l>>r;  
    cout<<rope.query(l,r)<<endl;
}