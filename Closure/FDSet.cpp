//
//  FDSet.cpp
//  Closure
//
//  Created by Loïs Paulin on 30/03/2017.
//  Copyright © 2017 Loïs Paulin. All rights reserved.
//

#include "FDSet.hpp"

FDSet::FDSet():tab(){}


FDSet::FDSet(const FDSet& set):tab(set.tab){}


bool FDSet::isIncluded(const FDSet& b) const{
	bool bIncluded = true;
	int i = 0, j=0;
	while (bIncluded && j<tab.size()){
		while (i<b.tab.size() && tab[i] < b.tab[j])
			++i;
		if (i==b.tab.size() || tab[i] > b.tab[j])
			bIncluded=false;
		++j;
	}
	return bIncluded;
}


const FDSet& FDSet::operator+=(const FDSet& b){
	std::vector<FD> out(tab.size() + b.tab.size());
	auto it = set_union(tab.begin(), tab.end(), b.tab.cbegin(), b.tab.cend(), out.begin());
	out.resize(it-out.begin());
	tab.swap(out);
	
	return *this;
}


const FDSet& FDSet::operator-=(const FDSet& b){
	std::vector<FD> out(tab.size() + b.tab.size());
	auto it = set_difference(tab.begin(), tab.end(), b.tab.begin(), b.tab.end(), out.begin());
	out.resize(it-out.begin());
	tab.swap(out);
	
	return *this;
}

void unite(const FDSet& a, const FDSet& b, FDSet& out){
	out.tab.resize(a.tab.size() + b.tab.size());
	auto it = set_union(a.tab.begin(), a.tab.end(), b.tab.begin(), b.tab.end(), out.tab.begin());
	out.tab.resize(it-out.tab.begin());
}

void diff(const FDSet& a, const FDSet& b, FDSet& out){
	out.tab.resize(a.tab.size() + b.tab.size());
	auto it = set_difference(a.tab.begin(), a.tab.end(), b.tab.begin(), b.tab.end(), out.tab.begin());
	out.tab.resize(it-out.tab.begin());
}

std::ostream& operator<<(std::ostream& out, const FDSet& a){
	for (int i = 0; i < a.tab.size() - 1; ++i){
		out << a.tab[i] << std::endl;
	}
	out << a.tab.back();
	
	return out;
}
