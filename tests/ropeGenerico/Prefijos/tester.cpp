/*
    Un caso de prueba consiste en lo siguiente:
    
    La primer linea consiste en dos numeros, n y q.
    
    La segunda linea contiene un array de largo n.
    
    Luego siguen q lineas donde cada una describe una operacion de rope
    que debe ejecutarse:
        * "1 k u": Actualizar el valor en la posicion k a u
        * "2 a b": Devolver el maximo de las sumas de los prefijos en el rango [a,b]

    La salida del caso de prueba son las respuestas a todas las operaciones
    de tipo 2.

    Los prefijos vacios tienen suma 0.

    Todos los indices empiezan en 1.
*/
#include <iostream>
#include <vector>
#include "../../../src/ropeGenerico.cpp"

using namespace std;

using ll = long long;

inline bool emptyInterval(Interval x) {
    return x.first>=x.second;
}

struct intervalo_prefijos {
    struct Value {
        ll max_p_sum; // maxima suma de un prefijo
        ll total_sum; // maxima suma total
    };

    static Value op(Value x, Value y) { 
        Value ans;
        ans.max_p_sum = max(x.max_p_sum,x.total_sum+y.max_p_sum);
        ans.total_sum = x.total_sum+y.total_sum;
        return ans;
    }
    static Value neut() { return {0LL,0LL}; } // elemento neutro para op

    static Value makeV(ll x) {
        Value ans;
        ans.max_p_sum = max(x,0LL);
        ans.total_sum = x;
        return ans;
    }
};



int main()
{
    int n,q;
    cin>>n>>q;
    Rope<intervalo_prefijos> rope(n);
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        rope.update(i,intervalo_prefijos::makeV(x));
    }
    while(q--)
    {
        int t,a,b;
        cin>>t>>a>>b;
        if(t==1)
            rope.update(a-1,intervalo_prefijos::makeV(b)); // -1 porque los indices empiezan en 1
        else
            cout<<rope.query(a-1,b).max_p_sum<<endl; // -1 porque rope usa intervalos cerrado abierto
    }
    return 0;
}