/*
    Un caso de prueba consiste en lo siguiente:
    
    La primer linea consiste en dos numeros, n y q.
    
    La segunda linea contiene un array de largo n.
    
    Luego siguen q lineas donde cada una describe una operacion de rope
    que debe ejecutarse:
        * "1 a b u": Sumar u a cada valor del rango [a,b].
        * "2 a b u": Reemplazar cada valor del rango [a,b] por u. 
        * "3 a b"  : Calcular la suma de los valores en el rango [a,b].

    La salida del caso de prueba son las respuestas a todas las operaciones
    de tipo 3.

    Todos los indices empiezan en 1.
*/
#include <iostream>
#include <vector>
#include "../../../src/ropeGenericoLazy.cpp"

using ll = long long;



struct ll_suma {
using Value = ll;
typedef struct {
    int t; // tipo de operacion
    ll v; // valor de la operacion
} Update;

    static Value op(Value x, Value y) { return x + y; } // una operacion asociativa
    static Value neut() { return 0; } // elemento neutro para op
    static Update up(Update x, Update y)
    {
        if(y.t == 2)
            return y; // Reemplazar le gana a todo
        // Si y es de suma, entonces hay que hacer
        // la operacion de x pero sumado con y.v
        x.v += y.v;
        return x;
    }
    static Value applyToInterval(Interval i, Value v, Update u)
    {
        if(u.t == 1)
            // sumar x.v
            return v+u.v*(i.second-i.first);
        // reemplazar todo por x.v
        return u.v*(i.second-i.first);
    }
    static Value input() { Value x; cin>>x; return x; }
};

using namespace std;

int main()
{
    int n,q;
    cin>>n>>q;
    Rope<ll_suma> rope(n);
    for(int i=0;i<n;i++)
        rope.update(i,{2,ll_suma::input()}); // reemplazar por el valor de entrada
    while(q--)
    {
        int t;
        cin>>t;
        if(t==1)
        {
            int a,b;
            ll u;
            cin>>a>>b>>u;
            rope.update_rango(a-1,b,{1,u}); // -1 porque los indices empiezan en 1
        }
        else if(t==2)
        {
            int a,b;
            ll u;
            cin>>a>>b>>u;
            rope.update_rango(a-1,b,{2,u}); // -1 porque los indices empiezan en 1
        }
        else
        {
            int a,b;
            cin>>a>>b;
            cout<<rope.query(a-1,b)<<endl; // -1 porque rope usa intervalos cerrado abierto
        }
    }
    return 0;
}