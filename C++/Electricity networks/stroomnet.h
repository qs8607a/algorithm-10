#ifndef __STROOMNET_H
#define __STROOMNET_H
#include "graaf.h"
#include <cassert>
#include <iostream>
#include <queue>
using namespace std;

template< class T >
class Pad:public std::vector< int >{
public:
    T geefCapaciteit() const{
        return capaciteit;
    }
    void zetCapaciteit(const T& _capaciteit){
        capaciteit=_capaciteit;
    }
friend ostream& operator<<(ostream& os, const Pad& p){
    os<<"Capaciteit= "<<p.capaciteit<<" :: ";
    if (p.size() > 0){
        os<<p[0];
    }
    for (unsigned int i=1; i<p.size(); i++ ){
        os<<"->"<<p[i];
    }
    os<<"\n";
	return os;
}
protected:
    T capaciteit;
};



template <class T>
class Vergrotendpad{

};


/**********************************************************************

   Class:Vergrotendpadzoeker
   
   beschrijving: Methodeklasse die, gegeven een stroomnetwerk,
                 en vergrotend pad teruggeeft.
                 van en naar zijn de knoopnummers van bron en doel.

   
***************************************************************************/
template <class T>
class Vergrotendpadzoeker : public Vergrotendpad<T>{
public:
    Vergrotendpadzoeker(const GraafMetTakdata<GERICHT,T>& stroomnetwerk, int van, int naar, Pad<T>& pad);
protected:
    virtual void foo(int t, int x);
    const GraafMetTakdata<GERICHT,T>& q;
    Pad<T>& p;
    vector<int> l;
    vector<bool> m;
    int v,v2;
};


template <class T>
Vergrotendpadzoeker<T>::Vergrotendpadzoeker(const GraafMetTakdata<GERICHT ,T>& _q,int _v,int _v2,Pad<T>& _p):
                    p(_p), q(_q),v(_v),v2(_v2),
                    l(q.aantalKnopen()), m(q.aantalKnopen(),false){
    p.clear();
    assert(v != v2);
    foo(v,0);
    assert(p.size()!=1);
    if (p.size() > 1){
        T g=*q.geefTakdata(p[0],p[1]);
        for (unsigned int i=2; i<p.size(); i++ ){
            T ychg=*q.geefTakdata(p[i-1],p[i]);
            if (ychg<g)
                g=ychg;
        }
        p.zetCapaciteit(g);
    }
}

template <class T>
void Vergrotendpadzoeker<T>::foo(int t,int x){
    m[t]=true;
    const typename GraafMetTakdata<GERICHT,T>::Knoop& a=q[t];
    int ychx=x+1;
    for (typename GraafMetTakdata<GERICHT,T>::Knoop::const_iterator it=a.begin();
                it!=a.end();it++){
        int u=it->first;
        if (*q.geefTakdata(t,u)> 0){
            if (it->first==v2 && ychx+1 > p.size()){
                l[v2]=t;
                p.resize(ychx+1);
                int ychf=v2;
                int i=ychx;
                while (ychf!=v){
                    p[i--]=ychf;
                    ychf=l[ychf];
                }
                p[0]=ychf;
            }
            else if(!m[u]){
                l[u]=t;
                foo(u,ychx);
            }
        }
    }
}


/**********************************************************************

   Class:VergrotendpadzoekerDijkstra
   
   beschrijving: Methodeklasse die, gegeven een stroomnetwerk,
                 en vergrotend pad teruggeeft adhv Dijkstra look a like.
                 van en naar zijn de knoopnummers van bron en doel.

   
***************************************************************************/
template <class T>
class VergrotendpadzoekerDijkstra : public Vergrotendpad<T>{
public:
    VergrotendpadzoekerDijkstra(const GraafMetTakdata<GERICHT,T>& stroomnetwerk, int van, int naar, Pad<T>& pad);
protected:
    const GraafMetTakdata<GERICHT,T>& q;
    Pad<T>& p;
    int v,v2;
};

struct verbinding {
	int knoop_from;
	int knoop_to;
	int weight;
	verbinding(int k, int l, int g) : knoop_from(k), knoop_to(l), weight(g) {};
	bool operator<(const verbinding& knoopje) const {
        return weight<knoopje.weight;   
    }
};
 

template <class T>
VergrotendpadzoekerDijkstra<T>::VergrotendpadzoekerDijkstra(const GraafMetTakdata<GERICHT ,T>& _q,int _v,int _v2,Pad<T>& _p):
                    p(_p), q(_q),v(_v),v2(_v2){
						
	priority_queue<verbinding> behandelen;
	vector<T> gewichten(q.aantalKnopen(),0);
	vector<T> pad(q.aantalKnopen(),-1);

	map<int,int> connecties = q[v];
	for(map<int,int>::iterator it = connecties.begin(); it != connecties.end(); it++){
			verbinding verb(v,it->first,*q.geefTakdata(v,it->first));
			gewichten[it->first] = *q.geefTakdata(v,it->first);
			pad[it->first] = v;
			behandelen.push(verb);
	}
	
	while(!behandelen.empty()){
		verbinding verb = behandelen.top();
		behandelen.pop();
		int volgende = verb.knoop_to;
		map<int,int> connecties = q[volgende];
		for(map<int,int>::iterator it = connecties.begin(); it != connecties.end(); it++){
			if(*q.geefTakdata(volgende,it->first) > 0 &&gewichten[it->first] < min(*q.geefTakdata(volgende,it->first),gewichten[volgende])){
				gewichten[it->first] = min(*q.geefTakdata(volgende,it->first),gewichten[volgende]);
				pad[it->first] = volgende;
				verbinding verb(volgende,it->first,*q.geefTakdata(volgende,it->first));
				behandelen.push(verb);
			}
		}
	}
	
	// Pad opbouwen
	p.clear();
	if(gewichten[v2]>0){
		int size = 1;
		int pos = 0;
		p.resize(size);
		p[pos] = v2;
		int go = v2;
		while(pad[go]!=v){
			p.resize(++size);
			p[++pos] = pad[go];
			go = pad[go];
		}
		p.resize(++size);
		p[++pos] = pad[go];
		reverse(p.begin(),p.end());
	}
	
	p.zetCapaciteit(gewichten[v2]);
	
}


/**********************************************************************

   Class: Stroomnetwerk
   
   beschrijving: Een stroomnetwerk gaat uit van een gewogen gerichte graaf
                 die in de constructor wordt opgegeven
   
***************************************************************************/

template <class T>//T = takdata
class Stroomnetwerk:public GraafMetTakdata<GERICHT, T >{
public:
//Copyconstructor. Let op: Graaf<GERICHT>(gr) moet toegevoegd,
//anders roept de copyconstructor van GraafMetTakdata de defaultconstructor
//van Graaf op en krijgen we een lege graaf.
Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr):
                    Graaf<GERICHT>(gr),GraafMetTakdata<GERICHT, T>(gr){};


friend Stroomnetwerk& operator -= (Stroomnetwerk<T> & restnetwerk, Pad<T> & pad) // output
{
    for (unsigned int i=1; i<pad.size(); i++ ){
		T * capaciteit = restnetwerk.geefTakdata(pad[i-1],pad[i]);
        *capaciteit = (*capaciteit) - pad.geefCapaciteit();
		if(restnetwerk.geefTakdata(pad[i],pad[i-1])==0)
			restnetwerk.voegVerbindingToe(pad[i],pad[i-1],pad.geefCapaciteit());
		else {
			T * capaciteit = restnetwerk.geefTakdata(pad[i],pad[i-1]);
	        *capaciteit = *capaciteit + pad.geefCapaciteit();
		}
    }
	return restnetwerk;
}

friend Stroomnetwerk & operator += (Stroomnetwerk<T> & netwerk, Pad<T> & pad){
	netwerk.capaciteit += pad.geefCapaciteit();
	// build path
	for (unsigned int i=1; i<pad.size(); i++ ){
		if(netwerk.geefTakdata(pad[i-1],pad[i])==0)
			netwerk.voegVerbindingToe(pad[i-1],pad[i],pad.geefCapaciteit());
		else {
			T * capaciteit = netwerk.geefTakdata(pad[i-1],pad[i]);
	        *capaciteit = *capaciteit + pad.geefCapaciteit();
		}
	}
	return netwerk;
}


T geefCapaciteit(){
	return capaciteit;
}

Stroomnetwerk(const GraafMetTakdata<GERICHT, T>& gr, int _van, int _naar, int type):
                    Graaf<GERICHT>(gr.aantalKnopen()),van(_van),naar(_naar){
						
	Stroomnetwerk<T> restnetwerk(gr);
    Pad<T> vergrotendpad;
	bepaalZoeker(type,restnetwerk, van, naar, vergrotendpad);
	capaciteit = 0;
    
	while(vergrotendpad.size() !=0 ){
        restnetwerk-=vergrotendpad;
        *this+=vergrotendpad;
        bepaalZoeker(type,restnetwerk, van, naar, vergrotendpad);
    }
}

void bepaalZoeker(int type,const GraafMetTakdata<GERICHT ,T>& q,int v,int v2,Pad<T>& p){
	if (type==1){
		Vergrotendpadzoeker<T> vg(q, v, v2, p);
	}
	else if (type==2){
		VergrotendpadzoekerDijkstra<T> vg(q, v, v2, p);
	}		
	else if (type==3){
		VergrotendpadzoekerDijkstra<T> vg(q, v, v2, p);
	}
}

protected:
int van,naar;
T capaciteit;
};
#endif
