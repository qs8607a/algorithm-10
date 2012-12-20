#ifndef __SIMULANNEAL_IMPL
#define __SIMULANNEAL_IMPL
#include "sa.h"
#include <math.h>
#include <iostream>
using namespace std;

template <class S>
class SimulatedAnnealing_Impl : public SimulatedAnnealing<S> {
public:
	SimulatedAnnealing_Impl(int x, int y, double ea_solution);
	SimulatedAnnealing_Impl(int x, int y, double ea_solution, int k0);
    double T;//temperatuur
    S *s;//voorlopige en eindoplossing.
    double T0();//initi"ele temperatuur
    bool terminateCond();//true als stoppen met zoeken
    double f(const S&);//objectieffunctie. Moet > 0 blijven
    S* newInitialSolution();
    S* newpickAtRandom(const S*);
    double p(double T, double deltaf);//probabiliteit verandering
    void updateT();
	
    S* newOplossing(){
        T=T0();
        s=newInitialSolution();
        while (!terminateCond()){
            S *sprime=newpickAtRandom(s);
            double deltaf=f(*sprime)-f(*s);
            if (deltaf < 0 || rand()<p(T,deltaf)*RAND_MAX){
                delete s;
                s=sprime;
            }else{
                delete sprime;
            }
            updateT();
        }
		cout << "Number of loops: " << k << endl;
        return s;
    }
	
private:
	int x,y;
	int k0;
	int k;
	double ea_solution;
};

template <class S>
SimulatedAnnealing_Impl<S>::SimulatedAnnealing_Impl(int x, int y, double ea_solution)
	:x(x),y(y),k0(0),k(1),ea_solution(ea_solution){}

template <class S>
SimulatedAnnealing_Impl<S>::SimulatedAnnealing_Impl(int x, int y, double ea_solution, int k0)
	:x(x),y(y),k(1),ea_solution(ea_solution){
		this->k0 = k0;
		if(k0<=0)
			this->k0 = 1;
	}

template <class S>
double SimulatedAnnealing_Impl<S>::T0(){
	return 1000.00;
}

template <class S>
bool SimulatedAnnealing_Impl<S>::terminateCond(){
	return f(*s)<=ea_solution;
}

template <class S>
void SimulatedAnnealing_Impl<S>::updateT(){
	k++;
	if(k0!=0)
		T = T/log(k+k0); // to slow
	else
		T *= ((double) rand() / (RAND_MAX)); // better 
}

template <class S>
double SimulatedAnnealing_Impl<S>::f(const S& s){
	return 1000*(1+cos((s.first/5+s.second/7.0)))+(1+cos(0.01*(s.first+s.second)))+0.0001*(sqrt(s.first*s.first+s.second*s.second));
}

template <class S>
double SimulatedAnnealing_Impl<S>::p(double T, double deltaf){
	return exp(-deltaf/T);
}

template <class S>
S* SimulatedAnnealing_Impl<S>::newInitialSolution(){
	S * p = new S();
	p->first = rand()%x;
	p->second = rand()%y;
	return p;
}

template <class S>
S* SimulatedAnnealing_Impl<S>::newpickAtRandom(const S* s){
	// calc neighborhood
	int maxx = x; int minx = 0;
	int maxy = y; int miny = 0;
	
	// neighborhood 10% from max value x & y
	int percx = (x*10)/100;
	int percy = (y*10)/100;
	if(s->first-percx>0)
		minx = s->first-percx;
	if(s->first+percx<x)
		maxx = s->first+percx;
	if(s->second-percy>0)
		miny = s->second-percy;
	if(s->second+percy<y)
		maxy = s->second+percy;
	
	// random value in neighborhood
	S * p = new S();
	p->first = rand()%(maxx-minx)+minx;
	p->second = rand()%(maxy-miny)+miny;
	return p;
}

#endif
