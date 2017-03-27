//
//  AttSet.hpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 27/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#ifndef AttSet_hpp
#define AttSet_hpp

#include <iostream>
#include <vector>
#include <string>
#include "Attribute.hpp"

//set of Attribute
class AttSet {
	
public:
	std::vector<Attribute> tab;
	// construct an empty set
	AttSet();
	// construct a set from a vector of Attribute
	AttSet(std::vector<Attribute>& initVect);
	// construct as a copy of another set of Attribute
	AttSet(const AttSet& set);
	// construct from a string describing a set of Attribute
	AttSet(const std::string& s);
	// in place union operator
	const AttSet& operator+=(const AttSet& b);
	// in place minus operator
	const AttSet& operator-=(const AttSet& b);
	// in place comparator, check if the set is included in the set b
	bool isIncluded(const AttSet& b) const;
	
	
	//set out to a union b
	friend void unite(const AttSet& a, const AttSet& b, AttSet& out);
	//set out ot a minus b
	friend void diff(const AttSet& a, const AttSet& b, AttSet& out);
	//printing operator, prints all attributes of the set separated by whitespaces
	friend std::ostream& operator<<(std::ostream& out, const AttSet& a);
};

//set out to a union b
void unite(const AttSet& a, const AttSet& b, AttSet& out);
//set out ot a minus b
void minus(const AttSet& a, const AttSet& b, AttSet& out);


#endif /* AttSet_hpp */
