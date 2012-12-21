//
//  main.cpp
//  Reeks 11 - Substring
//
//  Created by Wouter Peers & Cedric Verstraeten on 21/12/12.
//  Copyright (c) 2012 Wouter Peers & Cedric Verstraeten. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include "substring.h"
using namespace std;
int main(int argc, const char * argv[])
{
    ifstream reader("soera3.txt");
    string soran;
    if(reader.is_open()){
        stringstream buffer;
        buffer << reader.rdbuf();
		soran = buffer.str();
    } else {
        cout << "failed opening soera3.txt";
    }
    reader.close();
    
    ifstream reader2("lucas.txt");
    string lucas;
    if(reader2.is_open()){
        stringstream buffer2;
        buffer2 << reader2.rdbuf();
        lucas = buffer2.str();
    } else {
        cout << "failed opening lucas.txt";
    }
    reader2.close();
    
    LGD lgd(lucas,soran);
    cout << lgd.match();
    return 0;
}

