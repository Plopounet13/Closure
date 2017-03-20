//
//  main.cpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 20/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include "functions.hpp"

#define NAIVE 1
#define IMPROVED 2

using namespace std;

void usage(){
	cerr << "usage: closure option input atts" << endl;
	
	cerr << "option list:" << endl;
	cerr << "-naive: use the naive algorithm" << endl;
	cerr << "-improved: use the improved algortihm" << endl;
}

void error(const string& msg){
	cerr << endl << msg << endl;
}

int main(int argc, const char * argv[]) {
	
	if (argc != 4){
		error("Erreur nombre de parametre");
		usage();
		cerr << endl;
		exit(1);
	}
	
	int alg;
	
	if (!strcmp(argv[1] ,"-naive")){
		alg = NAIVE;
	}else if (!strcmp(argv[1] ,"-improved")){
		alg = IMPROVED;
	}
	
	ifstream in(argv[2]);
	if (in.fail()){
		error("Unable to open input file");
		exit(2);
	}
	
    return 0;
}
