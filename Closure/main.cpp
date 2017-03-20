//
//  main.cpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 20/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#include <iostream>

using namespace std;

void usage(){
	cerr << "usage: closure -";
}

void error(string& msg, int errNum){
	cerr << endl << msg << endl << endl;
	usage();
	exit(errNum);
}

int main(int argc, const char * argv[]) {
	
	if (argc != 4){
		error("Erreur nombre de parametre")
	}
	
    return 0;
}
