#include <concepts>
#include <iostream>
#include <vector>
#include "interval.cpp"

#define izq(n) (2*n+1)
#define der(n) (2*n+2)

using namespace std;

unsigned next_power_of_2(unsigned n)
{
    if(n==0)
        return 1;
    if((n & (n-1)) == 0)
        return n;           // ya es potencia de 2

    unsigned msb = 0;       // el bit mas significativo de n
    
    for(unsigned i=0;i<32;i++)
        if(n & (1<<i))
            msb = i;
            
    return 1<<(msb+1);
}
/*
b)
La propiedad que deben satifacer los valores almacenados en las hojas del rope
para cumplir las propiedades vistas en la introduccion y los costos sgueridos 
para las oepracioens son:
    * Ser asociativas
    * Poseer elemento neutro

(es decir los elementos y la operacion forman un Monoide)
*/


template<typename T>
concept Monoid = requires(T::Value a, T::Value b, T::Value c) {
typename T::Value; // hay un tipo de valores
{ T::op(a, b) } -> std::same_as<typename T::Value>; // clausura de la operacion
// T::op(a, T::op(b, c)) == T::op(T::op(a, b), c)   // asociatividad de la operacion
{ T::neut() } -> std::same_as<typename T::Value>;   // existencia del neutro
// T::op(a, T::neut()) == a // neutro por derecha
// T::op(T::neut(), a) == a // neutro por izquierda
};


template<typename Op>
requires Monoid<Op>
class Rope {
public:
    Rope(int n) { v.resize(2*next_power_of_2(n)+1, Op::neut()); N=n; }

    typename Op::Value query(int l, int r) { return query(l,r,0,0,N); }

    void update(int i, typename Op::Value x) { update_impl(0,0,N,i,x); }

private:
    std::vector<typename Op::Value> v;
    int N;

    // Realiza la consulta sobre el intervalo [l, r
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

    // Realiza la acutalizacion del indice i
    void update_impl(int nodo, int l_, int r_, int i, Op::Value x) {
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
        v[nodo] = Op::op(v[izq(nodo)], v[der(nodo)]); // actualizo de abajo hacia arriba
    }
};