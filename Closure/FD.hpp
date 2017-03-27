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
#include "AttSet.hpp"

//functional dependencies
class FD {
public:
	int ID;
	//functional dependency : left -> right
	AttSet left;
	AttSet right;
	//construct FD from two strings describing left Attribute and right Attributes
	FD(const std::string& left, const std::string& right, int ID);
	
	friend std::ostream& operator<< (std::ostream& out, const FD& fd);
};


#endif /* FD_hpp */
