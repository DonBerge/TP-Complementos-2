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
#include "../../src/ropeGenericoLazy.cpp"

using ll = long long;

vector<ll> a;

struct ll_suma {
using Value = ll;
using Update = ll;
    static Value input() { Value x; cin>>x; return x; }
};

using namespace std;

void updateRango(int l,int r, ll u)
{
    for(int i=l;i<r;i++)
        a[i]+=u;
}

ll query(int l,int r)
{
    ll ans = LONG_LONG_MIN;
    for(int i=l;i<r;i++)
        ans=max(ans,a[i]);
    return ans;
}


int main()
{
    int n,q;
    cin>>n>>q;
    for(int i=0;i<n;i++)
        a.push_back(ll_suma::input());    
    while(q--)
    {
        int t;
        cin>>t;
        if(t==1)
        {
            int a,b,u;
            cin>>a>>b>>u;
            updateRango(a-1,b,u); // -1 porque los indices empiezan en 1
        }
        else
        {
            int a,b;
            cin>>a>>b;
            cout<<query(a-1,b)<<endl; // -1 porque rope usa intervalos cerrado abierto
        }
    }
    return 0;
}