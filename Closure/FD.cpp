//
//  FD.cpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 27/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#include "FD.hpp"

using namespace std;

FD::FD(const string& left, const string& right, int id):left(left), right(right){
	ID = id;
}

ostream& operator<< (ostream& out, const FD& fd){
	out << fd.left << " -> " << fd.right;
	return out;
}
