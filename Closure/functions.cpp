//
//  functions.cpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 20/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#include <algorithm>
#include <sstream>
#include <list>
#include "functions.hpp"

using namespace std;

std::map<std::string, int> Attribute::mappage;
std::vector<std::string> Attribute::names;
int Attribute::counter = 0;

Attribute::Attribute(){
	ID=-1;
}

Attribute::Attribute(std::string& s){
	auto it = mappage.find(s);
	if (it != mappage.end()){
		ID = it->second;
	} else {
		ID = counter++;
		mappage[s] = ID;
		names.emplace_back();
		names[ID].swap(s);
	}
}

Attribute::Attribute(const Attribute& a){
	ID = a.ID;
}

bool operator<(const Attribute& a, const Attribute& b){
	return a.ID < b.ID;
}

bool operator>(const Attribute& a, const Attribute& b){
	return a.ID > b.ID;
}

bool operator<=(const Attribute& a, const Attribute& b){
	return a.ID <= b.ID;
}

bool operator>=(const Attribute& a, const Attribute& b){
	return a.ID >= b.ID;
}

bool operator==(const Attribute& a, const Attribute& b){
	return a.ID == b.ID;
}

std::ostream& operator<<(std::ostream& out, const Attribute& a){
	out << Attribute::names[a.ID];
	return out;
}


AttSet::AttSet(){}

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

bool AttSet::isIncluded(const AttSet& b) const{
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

FD::FD(const string& left, const string& right, int id):left(left), right(right){
	ID = id;
}

void closureNaive(const vector<FD>& sigma, const AttSet& x, AttSet& res, int algo){
	res = x;
	bool done = false;
	
	while (!done){
		done = true;
		//fd is of the form left -> right
		for (auto fd : sigma){
			// if left is in res and right is not
			if (res.isIncluded(fd.left) && !res.isIncluded(fd.right)){
				res += fd.right;
				done = false;
			}
		}
	}
}

void closureImproved(const vector<FD>& sigma, const AttSet& x, AttSet& res, int algo){
	vector<int> count(sigma.size());
	vector<list<const FD*>> l(Attribute::counter);
	
	for (int i=0; i < sigma.size(); ++i){
		count[i] = (int) sigma[i].left.tab.size();
		for (auto& att : sigma[i].left.tab){
			l[att.ID].push_back(&(sigma[i]));
		}
	}
	
	res=x;
	AttSet update=x;
	
	while (!update.tab.empty()){
		Attribute a = update.tab.back();
		update.tab.pop_back();
		
		for (const FD* fd : l[a.ID]){
			count[fd->ID] -= 1;
			if (!count[fd->ID]){
				AttSet Z_clos;
				diff(fd->right, res, Z_clos);
				update += Z_clos;
				res += Z_clos;
			}
		}
		
	}
}

void closure(const vector<FD>& sigma, const AttSet& x, AttSet& res, int algo){
	switch (algo) {
		case NAIVE:
			closureNaive(sigma, x, res, algo);
			return;
		case IMPROVED:
			closureImproved(sigma, x, res, algo);
			return;
	
  default:
			break;
	}
}
























