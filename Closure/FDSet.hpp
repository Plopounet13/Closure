//
//  FDSet.hpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 27/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#ifndef FDSet_hpp
#define FDSet_hpp

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include "Attribute.hpp"
#include "FD.hpp"


//set of Attribute


class FDSet {
	
public:
	std::vector<FD> tab;
	// construct an empty set
	FDSet();
	// construct as a copy of another set of FD
	FDSet(const FDSet& set);
	// in place union operator
	const FDSet& operator+=(const FDSet& b);
	// in place minus operator
	const FDSet& operator-=(const FDSet& b);
	// in place comparator, check if the set is included in the set b
	bool isIncluded(const FDSet& b) const;
	
	
	//set out to a union b
	friend void unite(const FDSet& a, const FDSet& b, FDSet& out);
	//set out ot a minus b
	friend void diff(const FDSet& a, const FDSet& b, FDSet& out);
	//printing operator, prints all FDs of the set separated by whitespaces
	friend std::ostream& operator<<(std::ostream& out, const FDSet& a);
};


#endif /* FDSet_hpp */
