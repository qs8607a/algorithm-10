#include "sa_impl.h"
#include <iostream>
using namespace std;

int main(){
	int x = 100000;
	int y = 100000;
	SimulatedAnnealing_Impl<pair<int,int> > sa(x,y,0.15);
	pair<int,int> * s; // 7615644
	cout << "Run forrest, run!" << endl;
	s = sa.newOplossing();
	cout << "x: " << s->first << " y: " << s->second << endl;
	cout << "solution: " << sa.f(*s);
	return 0;
}