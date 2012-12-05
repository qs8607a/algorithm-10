#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include "boyermoore.h"
using namespace std;
 
int main(){
	ifstream reader("bible.txt");
	if(!reader.is_open()){
		cerr << "not ok";
		return 1;
	}
	string pref = "God";
	const uchar prefix[]  =  "God";
	BoyerMoore bm(prefix,pref.size());
	stringstream buffer;
	buffer << reader.rdbuf();
	string str = buffer.str();
	const uchar * text = (uchar *) str.c_str();
	queue<const uchar*> store;
	bm.search(store,text,str.size());
	return 0;
}