#ifndef __SIMULANNEAL_IMPL
#define __SIMULANNEAL_IMPL
#include "sa.h"
#include "sat.h"
#include <math.h>
#include <iostream>
#include <iomanip.h>
#include <vector>
using namespace std;

template <class S>
class SimulatedAnnealing_ImplSAT : public SimulatedAnnealing<S> {
public:
	SimulatedAnnealing_ImplSAT(SAT & sat);
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
        
        return s;
    }
	
private:
	int k;
	SAT sat;
};

template <class S>
SimulatedAnnealing_ImplSAT<S>::SimulatedAnnealing_ImplSAT(SAT & sat):sat(sat),k(0){}

template <class S>
double SimulatedAnnealing_ImplSAT<S>::T0(){
	return 1000.00;
}

template <class S>
bool SimulatedAnnealing_ImplSAT<S>::terminateCond(){
	return f(*s)==sat.aantalVariabelen();
}

template <class S>
void SimulatedAnnealing_ImplSAT<S>::updateT(){
	k++;
	T *= ((double) rand() / (RAND_MAX)); // better 
}

template <class S>
double SimulatedAnnealing_ImplSAT<S>::f(const S& s){
	double count = 0;
	for(int i = 0; i < sat.aantalFormules(); i++){
		int j = 0;
		int k = 0;
		while(j<sat.aantalVariabelen() && sat[i][j]!=s[j]){
			j++;
		}
		if(sat[i][j]==s[j] && j<sat.aantalVariabelen()){
			count++;
		}
	}
    return count;
}

template <class S>
double SimulatedAnnealing_ImplSAT<S>::p(double T, double deltaf){
	return exp(-deltaf/T);
}

template <class S>
S* SimulatedAnnealing_ImplSAT<S>::newInitialSolution(){
	return new S(sat.aantalVariabelen(), 0);
}

template <class S>
S* SimulatedAnnealing_ImplSAT<S>::newpickAtRandom(const S* s){
	int i = 0;
	S * news;
	for(int j = 0; j < sat.aantalVariabelen()/4; j++){
		i = rand()%sat.aantalVariabelen();
		news = new S(*s);
		int random = rand()%3-1;
		(*news)[i] = random;
    }
	
    for(int k = 0; k < news->size(); k++){
        cout << setw(3) << (*news)[k];
    }
    cout << endl;
	
	return news;
}

#endif
