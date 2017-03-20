//
//  functions.cpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 20/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#include "functions.hpp"

AttSet::AttSet(){}

AttSet::AttSet(std::vector<attribute>& initVect){
	tab.swap(initVect)
}

AttSet::AttSet(const AttSet& set):tab(set.tab){}

const AttSet& AttSet::operator+=(const AttSet& b){
	
	vector<attribute> out;
	set_union(tab.begin(), tab.end(), b.tab.begin(), b.tab.end(), out.begin());
	tab.swap(out);
}

const AttSet& AttSet::operator-=(const AttSet& b){
	vector<attribute> out;
	set_difference(tab.begin(), tab.end(), b.tab.begin(), b.tab.end(), out.begin());
	tab.swap(out);
}

bool AttSet::isIncluded(const AttSet& b){
}


void unite(const AttSet& a, const AttSet& b, AttSet& out){
}

void minus(const AttSet& a, const AttSet& b, AttSet& out){
}


static int counter=0;

	int ID;
	AttSet left;
	AttSet right;

FD(const AttSet& left, const AttSet right){
}
