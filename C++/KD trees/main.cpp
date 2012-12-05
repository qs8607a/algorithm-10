#include "2DTree.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

struct point {
    int x, y;
    point() {}
    point(int _x, int _y) : x(_x), y(_y) {}
    point(const point& p):x(p.x),y(p.y){}
    void set(int _x, int _y) { x = _x; y = _y; }
    
    bool operator==(const point& p) const{
        return p.x==x && p.y==y;
    }
    friend std::ostream& operator<<(std::ostream& os, const point p2){
        return os<<"("<<setw(5)<<p2.x<<","<<setw(5)<<p2.y<<")";
    }
    unsigned int quadraticdistance(const point& p) const{
        return (p.x-x)*(p.x-x) + (p.y-y)*(p.y-y);
    }
};


int main(){
	K2DTree<point,string> tree;	
	ifstream reader;
	reader.open("points.txt");
	
	// Read file and create 2DTree
	string node;
	int x = 0; int y = 0;
	if(reader.is_open())
		while(getline(reader,node)){
		    stringstream ss(node);
			ss >> x >> y;
			point p(x,y);
			string data = "";
			tree.add(p,data);
		}
	
	// Search Nearest Point in 2DTree
	point search;
	for(unsigned int i = 0; i < 200; i+=10)
		for(unsigned int j = 0; j < 200; j+=10){
			search.set(i,j);
			tree.findNearestPoint(search);
		}
		
	int i;
	cin >> i;
	return 0;
}
