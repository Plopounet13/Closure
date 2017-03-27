//
//  functions.cpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 20/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#include <algorithm>
#include <random>
#include <sstream>
#include <list>
#include "functions.hpp"

using namespace std;

//TODO
bool AttSet::isIncluded(const AttSet& b) const{
	return true;
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
		
		//TODO: Think about a choosing heuristic
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

void generate(int n){
	
	vector<FD> sigma;
	string left, right;
	right = to_string(n);
	
	while (n--){
		left = to_string(n);
		sigma.emplace_back(left, right);
		right.swap(left);
	}
	
	auto engine = default_random_engine(time(NULL));
	shuffle(sigma.begin(), sigma.end(), engine);
	
	for (auto& fd : sigma){
		cout << fd << endl;
	}
	
}



void normalize(const vector<FD>& sigma){
	return;
}























