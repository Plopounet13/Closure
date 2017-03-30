//
//  FD.hpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 27/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#ifndef FD_hpp
#define FD_hpp

#include <string>
#include <iostream>
#include "Set.hpp"
#include "Attribute.hpp"

//functional dependencies
class FD {
public:
	int ID;
	//functional dependency : left -> right
	AttSet* left;
	AttSet* right;
	//construct FD from two strings describing left Attribute and right Attributes
	FD();
	FD(const FD& f);
	FD(const std::string& left, const std::string& right, int ID);
	FD(const AttSet& left, const AttSet& right, int ID);
	
	//FDs are ordered by their ID
	friend bool operator<(const FD& a, const FD& b);
	friend bool operator>(const FD& a, const FD& b);
	friend bool operator<=(const FD& a, const FD& b);
	friend bool operator>=(const FD& a, const FD& b);
	friend bool operator==(const FD& a, const FD& b);
	
	friend std::ostream& operator<< (std::ostream& out, const FD& fd);
	~FD();
};


#endif /* FD_hpp */
