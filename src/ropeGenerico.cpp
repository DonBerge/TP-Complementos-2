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


template<typename Op>
requires Monoid<Op>
class Rope {
public:
    Rope(int n) { v.resize(4*n, Op::neut()); N=n; }
    typename Op::Value query(int l, int r) { return query(l,r,0,0,N); }
    void update(int i, typename Op::Value x) { update_impl(0,0,N,i,x); }

private:
    std::vector<typename Op::Value> v;
    int N;

    Op::Value query(int l, int r, int i, int lp, int rp) {
        if(r<=l)
            return Op::neut();
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

    void update_impl(int nodo, int l_, int r_, int i, Op::Value x) {
        int l = i, r = i+1;
        if (l <= l_ && r_ <= r) { v[nodo] = x; return; }
        if (r <= l_ || r_ <= l) return;
        int m_ = (l_ + r_) / 2;
        // obs: una sola de estas dos llamadas hace algo, la otra cae en el caso base trivial
        //inmediatamente
        update_impl(izq(nodo), l_, m_, i, x);
        update_impl(der(nodo), m_, r_, i, x);
        v[nodo] = Op::op(v[izq(nodo)], v[der(nodo)]); // actualizo de abajo hacia arriba
    }
};