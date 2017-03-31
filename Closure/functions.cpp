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

void closureNaive(const FDSet& sigma, const AttSet& x, AttSet& res){
	res = x;
	bool done = false;
	
	while (!done){
		done = true;
		//fd is of the form left -> right
		for (auto fd : sigma.tab){
			// if left is in res and right is not
			if (res.isIncluded(*fd.left) && !res.isIncluded(*fd.right)){
				res += *fd.right;
				done = false;
			}
		}
	}
}

void closureImproved(const FDSet& sigma, const AttSet& x, AttSet& res){
	vector<int> count(sigma.tab.size());
	vector<list<pair<int, const FD*>>> l(Attribute::counter);
	
	res=x;
	AttSet update=x;
	
	for (int i=0; i < sigma.tab.size(); ++i){
		count[i] = (int) sigma.tab[i].left->tab.size();
		for (auto& att : sigma.tab[i].left->tab){
			l[att.ID].emplace_back(i, &(sigma.tab[i]));
		}
		if (!count[i]){
			update += *sigma.tab[i].right;
			res += *sigma.tab[i].right;
		}
	}
	
	while (!update.tab.empty()){
		
		//TODO: Think about a choosing heuristic
		Attribute a = update.tab.back();
		update.tab.pop_back();
		
		for (auto& p : l[a.ID]){
			const FD* fd = p.second;
			count[p.first] -= 1;
			if (!count[p.first]){
				AttSet Z_clos;
				diff(*(fd->right), res, Z_clos);
				update += Z_clos;
				res += Z_clos;
			}
		}
		
	}
}

void closure(const FDSet& sigma, const AttSet& x, AttSet& res, int algo){
	switch (algo) {
		case NAIVE:
			closureNaive(sigma, x, res);
			return;
		case IMPROVED:
			closureImproved(sigma, x, res);
			return;
	
		default:
			break;
	}
}

void generate(int n){
	
	FDSet sigma;
	string left, right;
	right = to_string(n);
	
	while (n--){
		left = to_string(n);
		sigma.tab.emplace_back(left, right);
		right.swap(left);
	}
	
	//This is not a good idea to shuffle a supposed sorted structure
	auto engine = default_random_engine(time(NULL));
	shuffle(sigma.tab.begin(), sigma.tab.end(), engine);
	
	cout << sigma << endl;
	
}

void closureImprovedWithout(const FDSet& sigma, const AttSet& x, AttSet& res, int except){
	vector<int> count(sigma.tab.size());
	vector<list<pair<int, const FD*>>> l(Attribute::counter);
	
	res=x;
	AttSet update=x;
	
	for (int i=0; i < sigma.tab.size(); ++i){
		if (sigma.tab[i].ID!=except){
			count[i] = (int) sigma.tab[i].left->tab.size();
			for (auto& att : sigma.tab[i].left->tab){
				l[att.ID].emplace_back(i, &(sigma.tab[i]));
			}
			if (!count[i]){
				update += *sigma.tab[i].right;
				res += *sigma.tab[i].right;
			}
		}
	}
	
	while (!update.tab.empty()){
		
		//TODO: Think about a choosing heuristic
		Attribute a = update.tab.back();
		update.tab.pop_back();
		
		for (auto& p : l[a.ID]){
			const FD* fd = p.second;
			count[p.first] -= 1;
			if (!count[p.first]){
				AttSet Z_clos;
				diff(*(fd->right), res, Z_clos);
				update += Z_clos;
				res += Z_clos;
			}
		}
		
	}
}


void minimize(const FDSet& sigma, FDSet& res){
	res.tab.clear();
	
	for (auto& fd : sigma.tab){
		AttSet right;
		closureImproved(sigma, *fd.left, right);
		res.tab.emplace_back(*fd.left, right);
	}
	
	for (auto it = res.tab.begin(); it != res.tab.end(); ++it){
		FD& fd = *it;
		AttSet test;
		closureImprovedWithout(res, *fd.left, test, fd.ID);
		if (test.isIncluded(*fd.right)){
			auto toDel = it--;
			res.tab.erase(toDel);
		}
	}
}


void reduce(const FDSet& sigma, FDSet& res){
	res = sigma;
	for (auto it = res.tab.begin(); it != res.tab.end(); ++it){
		FD& fd = *it;
		AttSet Y = *fd.right;
		AttSet& W = *fd.right;
		for (auto itA = W.tab.begin(); itA != W.tab.end(); ++itA){
			//We remove the attribute from right part
			Attribute tmpAtt = *itA;
			auto toDel = itA--;
			W.tab.erase(toDel);
		
			//If we can't deduce it from the new FD set then we put it back
			AttSet test;
			closureImproved(res, *fd.left, test);
			if (!test.isIncluded(Y)){
				++itA;
				itA = W.tab.insert(itA, tmpAtt);
			}
			
		}
	}
	
}


void normalize(FDSet& sigma){
	FDSet res;
	minimize(sigma, res);
	FDSet res2;
	reduce(res, res2);
	sigma.tab.swap(res2.tab);
}


void decompose(FDSet& sigma){
	return;
}




















