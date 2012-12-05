#ifndef __BOYERMOORE_H
#define __BOYERMOORE_H
#include <queue>
#include <vector>
typedef unsigned int uint;
typedef unsigned char uchar;
using namespace std;
class BoyerMoore{
public:
    BoyerMoore(const uchar* prefix,uint _prefixlength);
    void search(queue<const uchar*>& store,const uchar* text, uint textlength);
	int wrong_char(int i, int j, uchar k);
	int wrong_char_expanded(int i, int j, uchar k);
	int wrong_horspool(int i, int j, uchar k);
private:
	vector<int> prepare;
	vector<vector<int> > prepare_exp;
	vector<int> suffix;
	uint prefixlength;
	const uchar* prefix;
};
 
BoyerMoore::BoyerMoore(const uchar* _prefix,uint _prefixlength):prefixlength(_prefixlength),prefix(_prefix){
 
	prepare.resize(256,0);
	// initialize table most right occurrence in prefix
	// prefix : 	aba
	// prepare :	.... a(3) b(2) c(0) ....
	for(uint i = 0; i < _prefixlength;i++)
		prepare[prefix[i]] = i+1;
 
	// initialize expanded table most right occurrence in prefix from specific position
	// prefix : 	aba
	// prepare :	a : 1 1 3
	//				b : 0 2 2
	//				c : 0 0 0
	prepare_exp.resize(256,vector<int>(prefixlength));
	for(uint i = 0; i < 256;i++)
		for(uint j = 0; j < _prefixlength;j++)
			if(i == prefix[j])
				for(uint f = j; f < _prefixlength; f++)
			  	  prepare_exp[i][f] = j+1;
}
 
int BoyerMoore::wrong_char(int i, int j, uchar k){
	int jump;	
	jump = j + 1 - prepare[k];
	if(jump<0)
		jump = 1;
	return jump;
}
 
int BoyerMoore::wrong_char_expanded(int i, int j, uchar k){
	int jump = j + 1 - prepare_exp[k][j];
	return jump;
 
}
 
int BoyerMoore::wrong_horspool(int i, int j, uchar k){
	int jump = prefixlength - prepare[k];
	return jump;
}
 
void BoyerMoore::search(queue<const uchar*>& store,const uchar* text, uint textlength){
 
	int n = textlength;
	int m = prefixlength;
 
	int i = 0;
	int count = 0;
	int count_loops = 0;
	int d1; int d2; int d3;
	int k;
 
	while(i < n-m+1){
		k=1;&
		int j = m-1;
		bool good = true;
		while(j >= 0 && good){
			count_loops++;
			if(text[i+j]!=prefix[j]){
				d1 = wrong_char(i,j,text[i+j]);
				d2 = wrong_char_expanded(i,j,text[i+j]);
				d3 = wrong_horspool(i,j,text[i+m]);
				k = max(max(d1,d2),d3);
				good = false;
			}
			else
				j--;
		}
		if(j==-1){
			store.push(&text[i]);
			count++;
		}
		i+=k;
	}	
	cout <<"#found: " << count << " in " << count_loops << " loops. (length text: " << n << ")" << endl;
}
#endif