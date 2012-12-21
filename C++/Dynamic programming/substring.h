//
//  main.cpp
//  Reeks 11 - Substring
//
//  Created by Wouter Peers & Cedric Verstraeten on 21/12/12.
//  Copyright (c) 2012 Wouter Peers & Cedric Verstraeten. All rights reserved.
//


#ifndef Reeks_11___Substring_substring_h
#define Reeks_11___Substring_substring_h

#include <string>
#include <iomanip.h>
#include <vector>
#include <iostream>
using namespace std;

class LGD
{
public:
	LGD(string& str1,string& str2):str1(str1),str2(str2){};
	int match();
private:
	string str1;
	string str2;
};

int LGD:: match(){
	// initialize 2dim array
	unsigned int str1_size = str1.size()+1;
	unsigned int str2_size = str2.size()+1;
    
	vector<int>* prev_row = new vector<int>(str1_size,0);
	vector<int>* current_row = new vector<int>(str1_size,0);
	
	// 3 different cases
	int case1 = 0;
	int case2 = 0;
	int case3 = 0;
	
	// build arrays
	for(unsigned int i = 1; i < str1_size; i++){
		for(unsigned int j = 1; j < str2_size; j++){
			if(str1[i-1]==str2[j-1]){
				case1 = (*prev_row)[j-1]+1;
				(*current_row)[j] = case1;
			}
			else{
                case2 = (*current_row)[j-1];
                case3 = (*prev_row)[j];
				(*current_row)[j] = max(case2,case3);
            }
		}
		prev_row = current_row;
    }

	return (*current_row)[str2_size-1];
}



#endif
