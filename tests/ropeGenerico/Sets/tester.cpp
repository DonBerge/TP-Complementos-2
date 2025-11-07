/*
    Un caso de prueba consiste en lo siguiente:
    
    La primer linea consiste en dos numeros, n y q.
    
    La segunda linea contiene un array de largo n.
    
    Luego siguen q lineas donde cada una describe una operacion de rope
    que debe ejecutarse:
        * "1 k u": Actualizar el valor en la posicion k a u.
        * "2 a b": Chequear si todos los valores en el rango [a,b] son distintos.

    La salida del caso de prueba son las respuestas a todas las operaciones
    de tipo 2, respondiendo "YES" si todos los valores son distintos o "NO" si hay al
    menos dos valores iguales.

    Todos los indices empiezan en 1.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include "../../../src/ropeGenerico.cpp"

#define CHECK(b) (b ? "YES" : "NO")

using namespace std;

struct int_sets {
using Value = set<int>;
    static Value op(Value x, Value y) { 
        set<int> ans;
        ans.insert(x.begin(),x.end());
        ans.insert(y.begin(),y.end());
        return ans;
     } // una operacion asociativa
    static Value neut() { return set<int>(); } // elemento neutro para op
    static Value input() { int x; cin>>x; return makeV(x); }
    static Value makeV(int x) { set<int> s; s.insert(x); return s; }
};


int main()
{
    int n,q;
    cin>>n>>q;
    Rope<int_sets> rope(n);
    for(int i=0;i<n;i++)
        rope.update(i,int_sets::input());
    while(q--)
    {
        int t,a,b;
        cin>>t>>a>>b;
        if(t==1)
            rope.update(a-1,int_sets::makeV(b)); // -1 porque los indices empiezan en 1
        else
        {
            int len = b-a+1;
            int ans = rope.query(a-1,b).size();
            cout<<CHECK(len==ans)<<endl; // -1 porque rope usa intervalos cerrado abierto
        }
    }
    return 0;
}