/*
    Un caso de prueba consiste en lo siguiente:
    
    La primer linea consiste en dos numeros, n y q.
    
    La segunda linea contiene un array de largo n.
    
    Luego siguen q lineas donde cada una describe una operacion de rope
    que debe ejecutarse:
        * "1 k u": Actualizar el valor en la posicion k a u
        * "2 a b": Devolver la suma de los valores en el rango [a,b]

    La salida del caso de prueba son las respuestas a todas las operaciones
    de tipo 2.

    Todos los indices empiezan en 1.
*/
#include <iostream>
#include <vector>
#include "../../../src/ropeGenerico.cpp"

using namespace std;

using ll = long long;

struct ll_suma {
using Value = ll;
    static Value op(Value x, Value y) { return x + y; } // una operacion asociativa
    static Value neut() { return 0; } // elemento neutro para op
    static Value input() { Value x; cin>>x; return x; }
};


int main()
{
    int n,q;
    cin>>n>>q;
    Rope<ll_suma> rope(n);
    for(int i=0;i<n;i++)
        rope.update(i,ll_suma::input());
    while(q--)
    {
        int t,a,b;
        cin>>t>>a>>b;
        if(t==1)
            rope.update(a-1,b); // -1 porque los indices empiezan en 1
        else
            cout<<rope.query(a-1,b)<<endl; // -1 porque rope usa intervalos cerrado abierto
    }
    return 0;
}