/*
    Equivalente a los tests de ropeEnteros pero usa el ropeGenerico implementado con concepts

    Un caso de prueba consiste en lo siguiente:
    
    La primer linea consiste en dos numeros, n y q.
    
    La segunda linea contiene un array de largo n.
    
    Luego siguen q lineas donde cada una describe una operacion de rope
    que debe ejecutarse:
        * "1 k u": Actualizar el valor en la posicion k a u
        * "2 a b": Devolver el minimo de los valores en el rango [a,b]

    La salida del caso de prueba son las respuestas a todas las operaciones
    de tipo 2.

    Todos los indices empiezan en 1.
*/
#include <iostream>
#include <vector>
#include <climits>
#include "../../../src/ropeGenerico.cpp"

using namespace std;

struct unsigned_min {
using Value = unsigned;
    static Value op(Value x, Value y) { return min(x,y); } // una operacion asociativa
    static Value neut() { return INT_MAX; } // elemento neutro para op
    static Value input() { Value x; cin>>x; return x; }
};


int main()
{
    int n,q;
    cin>>n>>q;
    Rope<unsigned_min> rope(n);
    for(int i=0;i<n;i++)
        rope.update(i,unsigned_min::input());
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