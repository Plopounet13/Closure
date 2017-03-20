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
#include <map>

#define NAIVE 1
#define IMPROVED 2

//Attribute
class Attribute{
	static std::map<std::string, int> mappage;
	static std::vector<std::string> names;
	
public:
	static int counter;
	int ID;
	Attribute();
	Attribute(std::string& s);
	Attribute(const Attribute& a);
	
	//Attributes are ordered by their ID
	friend bool operator<(const Attribute& a, const Attribute& b);
	friend bool operator>(const Attribute& a, const Attribute& b);
	friend bool operator<=(const Attribute& a, const Attribute& b);
	friend bool operator>=(const Attribute& a, const Attribute& b);
	friend bool operator==(const Attribute& a, const Attribute& b);
	friend std::ostream& operator<<(std::ostream& out, const Attribute& a);
};

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

//functional dependencies
class FD {
public:
	int ID;
	//functional dependency : left -> right
	AttSet left;
	AttSet right;
	//construct FD from two strings describing left Attribute and right Attributes
	FD(const std::string& left, const std::string& right, int ID);
};

/*We use list of FDs to implement sets of FDs */ 

//compute the closure of x
void closure(const std::vector<FD>& sigma, const AttSet& x, AttSet& res, int algo);

#endif /* functions_hpp */

















