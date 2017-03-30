//
//  AttSet.cpp
//  Closure
//
//  Created by Loïs Paulin on 30/03/2017.
//  Copyright © 2017 Loïs Paulin. All rights reserved.
//

#include "AttSet.hpp"

AttSet::AttSet():tab(){}


AttSet::AttSet(const AttSet& set):tab(set.tab){}


AttSet::AttSet(const std::string& s){
	std::istringstream in(s);
	std::string att;
	while (in >> att) {
		tab.emplace_back(att);
	}
}


bool AttSet::isIncluded(const AttSet& b) const{
	bool bIncluded = true;
	int i = 0, j=0;
	while (bIncluded && j<b.tab.size()){
		while (i<tab.size() && tab[i] < b.tab[j])
			++i;
		if (i==tab.size() || tab[i] > b.tab[j])
			bIncluded=false;
		++j;
	}
	return bIncluded;
}


const AttSet& AttSet::operator+=(const AttSet& b){
	std::vector<Attribute> out(tab.size() + b.tab.size());
	auto it = set_union(tab.begin(), tab.end(), b.tab.begin(), b.tab.end(), out.begin());
	out.resize(it-out.begin());
	tab.swap(out);
	
	return *this;
}


const AttSet& AttSet::operator-=(const AttSet& b){
	std::vector<Attribute> out(tab.size() + b.tab.size());
	auto it = set_difference(tab.begin(), tab.end(), b.tab.begin(), b.tab.end(), out.begin());
	out.resize(it-out.begin());
	tab.swap(out);
	
	return *this;
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

std::ostream& operator<<(std::ostream& out, const AttSet& a){
	for (int i = 0; i < a.tab.size() - 1; ++i){
		out << a.tab[i] << " ";
	}
	out << a.tab.back();
	
	return out;
}
