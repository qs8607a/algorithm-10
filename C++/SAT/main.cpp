#include "sat.h"
#include "sa_implsat.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

int main(){
	SAT sat;
	sat.resize(1164,vector<int>(31,0));
	ifstream reader("satklein.dat");
	string lijn;
	getline(reader,lijn);
	int rij = 0;
    int maxy = 0;
	while(reader.good()){
		
		stringstream ss;
		string woord;
		ss << lijn;
		ss >> woord;
		int factor;
		int var = 0;
		while(ss.good())
		{
			factor = 1;
			if(woord.substr(0,1)=="o"){
				ss >> woord;
				continue;
			}
			else if(woord.substr(0,1)=="n"){
				factor = -1;
				ss >> woord;
			}
            
			var = atoi(woord.substr(1).c_str());
            maxy = max(var,maxy);
			sat[rij][var] = factor;
			ss >> woord;
		}
		rij++;
		getline(reader,lijn);
	}
 
    SimulatedAnnealing_ImplSAT<vector<int> > sa(sat);
	vector<int> * s = sa.newOplossing();
    for(int i = 0; i < sat.size(); i++){
     for(int j = 0; j < sat[i].size();j++)
     cout << setw(3) << sat[i][j];
     cout << endl;
        for(int k = 0; k < s->size(); k++){
            cout << setw(3) << (*s)[k];
        }
        cout << endl;
    }
    cout << endl;
   
	return 0;
}