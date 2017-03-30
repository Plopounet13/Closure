//
//  Attribute.cpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 27/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#include "Attribute.hpp"

using namespace std;

std::map<std::string, int> Attribute::mappage;
std::vector<std::string> Attribute::names;
int Attribute::counter = 0;

Attribute::Attribute(){
	ID=-1;
}

void Attribute::fromString(string& s){
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

Attribute::Attribute(std::string& s){
	fromString(s);
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


std::istream& operator>>(std::istream& in, Attribute& a){
	string s;
	in >> s;
	a.fromString(s);
	return in;
}
