#include <vector>

#define fst first
#define snd second

using namespace std;

//typedef pair<int,int> Interval;
using Interval = pair<int,int>;
Interval eInterval = {0,0};



int interval_len(Interval i)
{
    return i.snd - i.fst;
}

Interval interval_meet(Interval i, Interval j)
{
    int a = i.fst,b=i.snd,c=j.fst,d=j.snd;

    if(a<=c && d<=b)
        return {c,d};
    if(c<=a && b<=d)
        return {a,b};
    if(a<=c && b<=d)
        return {c,b};
    if(c<=a && d<=b)
        return {a,d};
    return eInterval;
}

bool interval_subset(Interval i, Interval j)
{
    return interval_meet(i,j)==i;
}