/*
    Un caso de prueba consiste en lo siguiente:
    
    La primer linea consiste en dos numeros, n y q.
    
    La segunda linea contiene un array de largo n.
    
    Luego siguen q lineas donde cada una describe una operacion de rope
    que debe ejecutarse:
        * "1 a b u": Sumar u a cada valor del rango [a,b]. 
        * "2 k": Devolver el valor del array en la posicion k.

    La salida del caso de prueba son las respuestas a todas las operaciones
    de tipo 2.

    Todos los indices empiezan en 1.
*/
#include <iostream>
#include <vector>
#include "../../src/ropeEnterosLazy.cpp"

using namespace std;

int main()
{
    int n,q;
    cin>>n>>q;
    Rope rope(n);
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        rope.update(i,x);
    }
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
            int k;
            cin>>k;
            cout<<rope.query(k-1,k)<<endl; // -1 porque rope usa intervalos cerrado abierto
        }
    }
    return 0;
}