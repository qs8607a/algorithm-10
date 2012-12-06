#include "stroomnet.h"
#include "stroomnetwerkgenerator.h"
#include "graaf.h"
using namespace std;

enum types { NORMAAL = 1, DIJKSTRA = 2, SHORTEST = 3};

int main(){
	
	
    GraafMetTakdata <GERICHT,int> gr(8);
    gr.voegVerbindingToe(1,2,7 );
    gr.voegVerbindingToe(7,1,2 );
    gr.voegVerbindingToe(7,3,6 );
    gr.voegVerbindingToe(3,4,7 );
    gr.voegVerbindingToe(4,5,1 );
    gr.voegVerbindingToe(2,5,4 );
    gr.voegVerbindingToe(1,0,9 );
    gr.voegVerbindingToe(0,2,3 );
    gr.voegVerbindingToe(0,7,5 );
    gr.voegVerbindingToe(0,6,6 );
    gr.voegVerbindingToe(5,6,6 );
    gr.voegVerbindingToe(6,3,2 );
    gr.voegVerbindingToe(6,4,8 );
	
	GraafMetTakdata <GERICHT,int> gr_test(5);
	gr_test.voegVerbindingToe(0,1,10);
	gr_test.voegVerbindingToe(0,2,6);
	gr_test.voegVerbindingToe(0,4,10);
	gr_test.voegVerbindingToe(1,2,3);
	gr_test.voegVerbindingToe(2,3,7);
	gr_test.voegVerbindingToe(3,4,4);
	gr_test.voegVerbindingToe(4,2,5);
	gr_test.voegVerbindingToe(4,3,15);
	
	Stroomnetwerk<int> sn_N(gr_test,3,2,NORMAAL);
	Stroomnetwerk<int> sn_D(gr_test,3,2,DIJKSTRA);
	cout << sn_N.geefCapaciteit() << " -- " << sn_D.geefCapaciteit() << endl;

	return 0;
}