//
//  Attribute.hpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 27/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#ifndef Attribute_hpp
#define Attribute_hpp

#include <iostream>
#include <map>
#include <vector>

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

#endif /* Attribute_hpp */
