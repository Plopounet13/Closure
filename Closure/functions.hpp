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
#include "Attribute.hpp"
#include "AttSet.hpp"
#include "FD.hpp"
#include "FDSet.hpp"

#define NAIVE 1
#define IMPROVED 2

//TODO: Finir transiion vers sets

/*We use list of FDs to implement sets of FDs */ 

//Computes the closure of x
void closure(const FDSet& sigma, const AttSet& x, AttSet& res, int algo);

//Generates a signature of the form n-1 -> n ,...
void generate(int n);

//Normalizes the signature sigma
void normalize(const FDSet& sigma);

//Outputs BCNF corresponding to signature sigma
void decompose(const FDSet& sigma);

#endif /* functions_hpp */

















