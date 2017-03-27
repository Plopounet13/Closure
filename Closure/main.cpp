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
#include <sstream>
#include <list>
#include <map>
#include "functions.hpp"

using namespace std;

void filterComments(istream& in, ostream& out){
	
	string s;
	while (getline(in, s)){
		istringstream ss(s);
		char c;
		if (ss >> c)
			if (c != '#'){
				out << s << endl;
			}
	}
	
}

void constructFDList(istream& in, vector<FD>& sigma){
	
	string s;
	int nb=0;
	while (getline(in, s)){
		istringstream ss(s);
		string left, right;
		char trash;
		
		getline(ss, left, '-');
		ss >> trash;
		getline(ss, right);
		
		sigma.emplace_back(left, right, nb++);
	}
}

void usage(){
	cerr << "usage: closure algorithm input atts" << endl;
	
	cerr << "algorithms list:" << endl;
	cerr << "-naive: use the naive algorithm" << endl;
	cerr << "-improved: use the improved algortihm" << endl << endl;
	
	cerr << "usage: closure function parameter" << endl;
	
	cerr << "functions list:" << endl;
	cerr << "-generate: parameter is an integer n." << endl << "\tGenerate list of relation from \"n-1 -> n\" to \"0 -> 1\"" << endl;
	cerr << "-normalize: parameter is an signature file." << endl << "\tNormalizes the input signature and prints it on standard output" << endl;
	cerr << "-decompose: parameter is a normalized signature file." << endl;
	cerr << "\tPrints a BCNF schema corresponding to the input signature on the standard output" << endl << endl;
	
}

void error(const string& msg){
	cerr << endl << msg << endl;
}

int mainClosure(const char* argv[]){
	
	int alg;
	
	if (!strcmp(argv[1] ,"-naive")){
		alg = NAIVE;
	} else if (!strcmp(argv[1] ,"-improved")){
		alg = IMPROVED;
	} else {
		error("Erreur: type d'algorithme de fermeture inconnu");
		usage();
		exit(2);
	}
	 
	ifstream in(argv[2]);
	if (in.fail()){
		error("Erreur: impossible d'ouvrir le fichier d'entrée");
		usage();
		exit(4);
	}
	
	vector<FD> sigma;
	
	stringstream tmpout;
	
	filterComments(in, tmpout);
	constructFDList(tmpout, sigma);
	
	AttSet x(argv[3]);
	AttSet res;
	
	closure(sigma, x, res, alg);
	
	cout << res << endl;
	
	return 0;
}

bool is_integer(const string s){
	for (char c : s){
		if (c < '0' || c > '9'){
			return false;
		}
	}
	return true;
}

int mainOther(const char* argv[]){
	
	if (!strcmp(argv[1] ,"-generate")){
		int n;
		if (!is_integer(argv[2])){
			error("Erreur: second parametre de type incorrect");
			usage();
			exit(3);
		}
		n = atoi(argv[2]);
		generate(n);
		
	} else if (!strcmp(argv[1] ,"-normalize")){
		
		
		ifstream in;
		stringstream tmpout;
		vector<FD> sigma;
		if (strcmp(argv[2], "-")){
			in = ifstream(argv[2]);
			if (in.fail()){
				error("Erreur: impossible d'ouvrir le fichier d'entrée");
				usage();
				exit(4);
			}
			
			filterComments(in, tmpout);
		}else{
			filterComments(cin, tmpout);
		}
		
		constructFDList(tmpout, sigma);
		
		normalize(sigma);
		
	} else if (!strcmp(argv[1] ,"-decompose")){
		
		ifstream in(argv[2]);
		if (in.fail()){
			error("Erreur: impossible d'ouvrir le fichier d'entrée");
			usage();
			exit(4);
		}
		
		
		vector<FD> sigma;
		
		stringstream tmpout;
		
		filterComments(in, tmpout);
		constructFDList(tmpout, sigma);
		
		decompose(sigma);
		
	} else {
		error("Erreur: fonctinon demandée non reconnue");
		usage();
		exit(2);
	}
	
	return 0;
}

int main(int argc, const char * argv[]) {
	
	if (argc == 4){
		return mainClosure(argv);
	} else if (argc == 3){
		return mainOther(argv);
	} else {
		error("Erreur: nombre de parametres incorrect");
		usage();
		exit(1);
	}
	
}















