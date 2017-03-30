//
//  FD.cpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 27/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#include "FD.hpp"

using namespace std;

FD::FD(){}

FD::FD(const AttSet& l, const AttSet& r, int id){
	left = new AttSet(l);
	right = new AttSet(r);
	ID = id;
}

FD::FD(const string& l, const string& r, int id){
	left = new AttSet(l);
	right = new AttSet(r);
	ID = id;
}

FD::FD(const FD& f){
	left = new AttSet(*f.left);
	right = new AttSet(*f.right);
	ID = f.ID;
}

bool operator<(const FD& a, const FD& b){
	return a.ID < b.ID;
}

bool operator>(const FD& a, const FD& b){
	return a.ID > b.ID;
}

bool operator<=(const FD& a, const FD& b){
	return a.ID <= b.ID;
}

bool operator>=(const FD& a, const FD& b){
	return a.ID >= b.ID;
}

bool operator==(const FD& a, const FD& b){
	return a.ID == b.ID;
}

ostream& operator<< (ostream& out, const FD& fd){
	out << *fd.left << " -> " << *fd.right;
	return out;
}

FD::~FD() {
	delete left;
	delete right;
}
