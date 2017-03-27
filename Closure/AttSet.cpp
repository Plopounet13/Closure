//
//  AttSet.cpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 27/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#include <sstream>
#include "AttSet.hpp"

using namespace std;

AttSet::AttSet():tab(){}

AttSet::AttSet(std::vector<Attribute>& initVect){
	tab.swap(initVect);
}

AttSet::AttSet(const AttSet& set):tab(set.tab){}

AttSet::AttSet(const std::string& s){
	istringstream in(s);
	string att;
	while (in >> att) {
		tab.push_back(att);
	}
}

const AttSet& AttSet::operator+=(const AttSet& b){
	vector<Attribute> out(tab.size() + b.tab.size());
	auto it = set_union(tab.begin(), tab.end(), b.tab.begin(), b.tab.end(), out.begin());
	out.resize(it-out.begin());
	tab.swap(out);
	
	return *this;
}

const AttSet& AttSet::operator-=(const AttSet& b){
	vector<Attribute> out(tab.size() + b.tab.size());
	auto it = set_difference(tab.begin(), tab.end(), b.tab.begin(), b.tab.end(), out.begin());
	out.resize(it-out.begin());
	tab.swap(out);
	
	return *this;
}
std::ostream& operator<<(std::ostream& out, const AttSet& a){
	for (int i = 0; i < a.tab.size() - 1; ++i){
		out << a.tab[i] << " ";
	}
	out << a.tab.back();
	
	return out;
}

void unite(const AttSet& a, const AttSet& b, AttSet& out){
	out.tab.resize(a.tab.size() + b.tab.size());
	auto it = set_union(a.tab.begin(), a.tab.end(), b.tab.begin(), b.tab.end(), out.tab.begin());
	out.tab.resize(it-out.tab.begin());
}

void diff(const AttSet& a, const AttSet& b, AttSet& out){
	out.tab.resize(a.tab.size() + b.tab.size());
	auto it = set_difference(a.tab.begin(), a.tab.end(), b.tab.begin(), b.tab.end(), out.tab.begin());
	out.tab.resize(it-out.tab.begin());
}
