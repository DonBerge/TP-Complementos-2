#include <vector>

#define fst first
#define snd second

using namespace std;

//typedef pair<int,int> Interval;
using Interval = pair<int,int>;
Interval eInterval = {0,0};


// Realizamos la interseccion de los itervalos i y j
Interval interval_meet(Interval i, Interval j)
{
    int a = i.fst,b=i.snd,c=j.fst,d=j.snd;

    if(a<=c && d<=b)
        return {c,d};
    else if(c<=a && b<=d)
        return {a,b};
    else if(a<=c && b<=d)
        return {c,b};
    else if(c<=a && d<=b)
        return {a,d};
    return eInterval;
}

// Revisamos que el intervalo i este completamente incluido en el intevalo j
bool interval_subset(Interval i, Interval j)
{
    return interval_meet(i,j)==i;
}