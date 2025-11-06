#include <concepts>
#include <iostream>
#include <vector>
#include "interval.cpp"

#define izq(n) (2*n+1)
#define der(n) (2*n+2)

using namespace std;

/*
    + = T
    * = U
    
    Para poder combinar actualizaciones, se tiene que cumplir que:
    (v*u)*w = v*(u*w)
    Es decir, * tiene que ser asociativa

    Para poder calcular el resultado sin recursionar, es necesario que * sea
    distributiva sobre +.
    a*u + b*u + c*u = (a+b+c)*u

    a+u+b+u+c+u
    =
    (a+b+c)+u*n

    (a=u) + (b=u) + (c=u)
    =
    ((a+b+c)=u)*n
*/

template<typename T>
concept Monoid = requires(T::Value a, T::Value b, T::Value c) {
typename T::Value; // hay un tipo de valores
{ T::op(a, b) } -> std::same_as<typename T::Value>; // clausura de la operacion
// T::op(a, T::op(b, c)) == T::op(T::op(a, b), c) // asociatividad de la operacion
{ T::neut() } -> std::same_as<typename T::Value>; // existencia del neutro
// T::op(a, T::neut()) == a // neutro por derecha
// T::op(T::neut(), a) == a // neutro por izquierda
};

template<typename T>
concept Updater = Monoid<T> && requires(T::Value a, T::Update b, T::Update c, Interval i) {
typename T::Update; // hay un tipo de actualizaciones
{ T::up(a, b) } -> std::same_as<typename T::Update>; // clausura de la operacion
// T::up(a, T::up(b, c)) == T::up(T::up(a, b), c) // asociatividad de la operacion
{ T::uneut() } -> std::same_as<typename T::Update>; 
{ T::applyToInterval(i, a, b)} -> std::same_as<typename T::Value>;
// i = Intervalo donde se ejecuta la actualizacion
// a = Valor correspondiente al intervalo
// b = Valor de la actualizacion combinada
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
requires Updater<Op>
class Rope {
public:
    // Construye un rope vacio de tamaño n
    Rope(int n) { v.resize(4*n, Op::neut()); N=n; lazy.resize(4*n,Op::uneut()); }
    // Construye un rope a partir de un array
    Rope(vector<typename Op::Value>& a) : Rope(a.size()) { // primero construyo el rope vacio con N=a.size()
        build(a,0,0,a.size()); // Luego llamo a build usando el array a
    }
    
    typename Op::Value query(int l, int r) { return query(l,r,0,0,N); }
    void update(int i, Op::Update x) { update_rango(i,i+1,x); }
    void update_rango(int l, int r, Op::Update x) { update_impl(0,0,N,l,r,x);}

    
private:
    std::vector<typename Op::Value> v;
    std::vector<typename Op::Update> lazy;
    std::vector<bool> markForUpdate;
    int N;

    // Ya no es posible construir el rope haciendo un update por cada elemento del array
    // ya que la operacion de actualizacion puede diferir de la de consulta.
    // Por lo tanto tenemos una funcion para construir el rope a partir de un vector
    void build(vector<typename Op::Value>& a,int node, int lp, int rp)
    {
        if(rp<=lp)
            return;
        if(rp-lp==1) // hoja
            v[node] = a[lp];
        else
        {
            int m = (lp + rp)/2;
            build(a,izq(node),lp,m);
            build(a,der(node),m,rp);
            v[node]=Op::op(v[izq(node)],v[der(node)]);
        }
    }
    
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

    void update_impl(int node, int l_, int r_, int l, int r, Op::Update upd) {
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
            lazy[izq(node)] = Op::up(lazy[izq(node)], lazy[node]);
            lazy[der(node)] = Op::up(lazy[der(node)], lazy[node]);
        }
        v[node] = Op::applyToInterval({l_,r_},v[node],lazy[node]);
        lazy[node] = Op::uneut();
    }
};