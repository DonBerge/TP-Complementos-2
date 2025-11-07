/*
    Un caso de prueba consiste en lo siguiente:
    
    La primer linea consiste en dos numeros, n y q.
    
    La segunda linea contiene un array de largo n.
    
    Luego siguen q lineas donde cada una describe una operacion de rope
    que debe ejecutarse:
        * "1 a b u": Sumar u a cada valor del rango [a,b]. 
        * "2 a b": Devolver el maximo valor en el rango [a,b].

    La salida del caso de prueba son las respuestas a todas las operaciones
    de tipo 2.

    Todos los indices empiezan en 1.
*/
#include <iostream>
#include <vector>
#include <climits>
#include "../../../src/ropeGenericoLazy.cpp"

using ll = long long;

struct ll_suma {
using Value = ll;
using Update = ll;
    static Value op(Value x, Value y) { return max(x,y); } // una operacion asociativa
    static Value neut() { return LONG_LONG_MIN; } // elemento neutro para op
    static Update up(Update x, Update y) { return x + y; }
    static Update applyToInterval(Interval i, Value v, Update u) { 
        if(v==LONG_LONG_MIN)
            return LONG_LONG_MIN;
        return v+u;
     }
    static Value input() { Value x; cin>>x; return x; }
};

using namespace std;

int main()
{
    int n,q;
    cin>>n>>q;
    vector<ll> a;
    for(int i=0;i<n;i++)
        a.push_back(ll_suma::input());    
    Rope<ll_suma> rope(a);
    while(q--)
    {
        int t;
        cin>>t;
        if(t==1)
        {
            int a,b,u;
            cin>>a>>b>>u;
            rope.update_rango(a-1,b,u); // -1 porque los indices empiezan en 1
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