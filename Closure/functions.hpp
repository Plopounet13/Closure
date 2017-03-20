//
//  functions.hpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 20/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

//attribute
typedef std::string attribute;

//set of attribute
class AttSet {
	std::vector<attribute> tab;
	
public:
	// construct an empty set
	AttSet();
	// construct a set from a vector of attribute
	AttSet(std::vector<attribute>& initVect);
	// construct as a copy of another set of attribute
	AttSet(const AttSet& set); 
	// in place union operator
	const AttSet& operator+=(const AttSet& b); 
	// in place minus operator
	const AttSet& operator-=(const AttSet& b);
	//in place comparator, check if the set is included in the set b
	bool isIncluded(const AttSet& b);
};

//set out to a union b
void unite(const AttSet& a, const AttSet& b, AttSet& out);
//set out ot a minus b
void minus(const AttSet& a, const AttSet& b, AttSet& out);

//functional dependencies
class FD {
	//number of FDs already created, to give them a unique identifier
	static int counter;
public:
	//identifier of the FD
	int ID;
	//functional dependency : left -> right
	AttSet left;
	AttSet right;
	//construct FD from two sets of attributes
	FD(const AttSet& left, const AttSet right);
};

int FD::counter=0;

/*We use list of FDs to implement sets of FDs */ 

//compute the closure of x
void closure(const std::list<FD>& sigma, const AttSet& x, AttSet& res, int algo);

#endif /* functions_hpp */

















