#include <concepts>
#include <iostream>
#include <vector>
#include "interval.cpp"

#define izq(n) (2*n+1)
#define der(n) (2*n+2)

using namespace std;

template<typename T>
concept Monoid = requires(T::Value a, T::Value b, T::Value c) {
typename T::Value; // hay un tipo de valores
{ T::op(a, b) } -> std::same_as<typename T::Value>; // clausura de la operacion
// T::op(a, T::op(b, c)) == T::op(T::op(a, b), c) // asociatividad de la operacion
{ T::neut() } -> std::same_as<typename T::Value>; // existencia del neutro
// T::op(a, T::neut()) == a // neutro por derecha
// T::op(T::neut(), a) == a // neutro por izquierda
//{ T::inv(a) } -> std::same_as<typename T::Value>; // clausura del inverso
// T::op(a, T::inv(a)) == T::neut() // inverso por derecha
// T::op(T::inv(a), a) == T::neut() // inverso por izquierda
};

template<typename T>
requires Monoid<T>
T::Value powa(typename T::Value v, int i)
{
    auto res = T::neut();
    while(i > 0)
    {
        if(i & 1)
            res = T::op(res,v);
        v = T::op(v,v);
        i >>= 1;
    }
    return res;
}

template<typename Op>
requires Monoid<Op>
class Rope {
public:
    Rope(int n) { v.resize(4*n, Op::neut()); N=n; lazy.resize(4*n, Op::neut()); }
    typename Op::Value query(int l, int r) { return query(l,r,0,0,N); }
    void update(int i, Op::Value x) { update_rango(i,i+1,x); }
    void update_rango(int l, int r, Op::Value x) { update_impl(0,0,N,l,r,x);}

    
private:
    std::vector<typename Op::Value> v;
    std::vector<typename Op::Value> lazy;
    int N;

    Op::Value query(int l, int r, int i, int lp, int rp) {
        if(r<=l)
            return Op::neut();

        propagate(i,lp,rp);
        
        if(interval_subset({lp,rp},{l,r}))
            return v[i];
        
        Interval m = interval_meet({l,r},{lp,rp});        
        if(m == eInterval)
            return Op::neut();

        int mid = (lp+rp)/2;

        
        Interval ml = interval_meet(m, {lp,mid});
        Interval mr = interval_meet(m, {mid, rp});
        return
            Op::op(
                query(ml.first,ml.second, izq(i), lp, mid),
                query(mr.first,mr.second, der(i), mid, rp)    
            );
    }

    void update_impl(int node, int l_, int r_, int l, int r, Op::Value upd) {
        propagate(node, l_, r_);
        if (l <= l_ && r_ <= r) { lazy[node] = upd; propagate(node, l_, r_); return; }
        if (r <= l_ || r_ <= l) { return; }
        int m_ = (l_ + r_) / 2;
        update_impl(izq(node), l_, m_, l, r, upd);
        update_impl(der(node), m_, r_, l, r, upd);
        v[node] = Op::op(v[izq(node)], v[der(node)]);
    }

    void propagate(int node, int l_, int r_) {
        int len = r_ - l_;
        if (len > 1) { // no es hoja, combino actualizaciones en los hijos
            lazy[izq(node)] = Op::op(lazy[izq(node)], lazy[node]);
            lazy[der(node)] = Op::op(lazy[der(node)], lazy[node]);
        }
        v[node] = Op::op(v[node], powa<Op>(lazy[node],len));
        lazy[node] = Op::neut();
    }
};