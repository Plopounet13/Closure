//
//  Set.hpp
//  Closure
//
//  Created by Hugo Menet and Loïs Paulin on 27/03/2017.
//  Copyright © 2017 Hugo Menet and Loïs Paulin. All rights reserved.
//

#ifndef Set_hpp
#define Set_hpp

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include "Attribute.hpp"
#include "FD.hpp"


//set of Attribute

template <class T>
class Set {
	
public:
	std::vector<T> tab;
	
	// construct an empty set
	Set();
	
	// construct as a copy of another set of FD
	Set(const Set& set);
	
	// in place union operator
	const Set& operator+=(const Set& b);
	
	// in place minus operator
	const Set& operator-=(const Set& b);
	
	// in place comparator, check if the set is included in the set b
	bool isIncluded(const Set& b) const;
	
	//set out to a union b
	friend void unite(const Set<T>& a, const Set<T>& b, Set<T>& out){
		out.tab.resize(a.tab.size() + b.tab.size());
		auto it = set_union(a.tab.begin(), a.tab.end(), b.tab.begin(), b.tab.end(), out.tab.begin());
		out.tab.resize(it-out.tab.begin());
	}
	
	//set out ot a minus b
	friend void diff(const Set<T>& a, const Set<T>& b, Set<T>& out){
		out.tab.resize(a.tab.size() + b.tab.size());
		auto it = set_difference(a.tab.begin(), a.tab.end(), b.tab.begin(), b.tab.end(), out.tab.begin());
		out.tab.resize(it-out.tab.begin());
	}
	
	//printing operator, prints all FDs of the set separated by whitespaces
	friend std::ostream& operator<<(std::ostream& out, const Set<T>& a){
		for (int i = 0; i < a.tab.size() - 1; ++i){
			out << a.tab[i] << std::endl;
		}
		out << a.tab.back();
		
		return out;
	}

	
};

template <class T>
Set<T>::Set():tab(){}


template <class T>
Set<T>::Set(const Set<T>& set):tab(set.tab){}


template <class T>
bool Set<T>::isIncluded(const Set<T>& b) const{
	bool bIncluded = true;
	int i = 0, j=0;
	while (bIncluded && j<tab.size()){
		while (i<b.tab.size() && tab[i] < b.tab[j])
			++i;
		if (i==b.tab.size() || tab[i] > b.tab[j])
			bIncluded=false;
		++j;
	}
	return bIncluded;
}


template <class T>
const Set<T>& Set<T>::operator+=(const Set<T>& b){
	std::vector<T> out(tab.size() + b.tab.size());
	auto it = set_union(tab.begin(), tab.end(), b.tab.cbegin(), b.tab.cend(), out.begin());
	out.resize(it-out.begin());
	tab.swap(out);
	
	return *this;
}


template <class T>
const Set<T>& Set<T>::operator-=(const Set<T>& b){
	std::vector<T> out(tab.size() + b.tab.size());
	auto it = set_difference(tab.begin(), tab.end(), b.tab.begin(), b.tab.end(), out.begin());
	out.resize(it-out.begin());
	tab.swap(out);
	
	return *this;
}

typedef Set<FD> FDSet ;

#endif /* Set_hpp */
