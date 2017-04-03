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

class FD;


//set of Attribute

template <class T>
class Set {
	
public:
	//TODO: Once all algorithm finished try replacing by a list and time it
	std::vector<T> tab;
	
	// construct an empty set
	Set();
	
	~Set(){}
	
	// construct as a copy of another set
	Set(const Set& set);
	
	// construct from string describing the set
	Set(const std::string& s);
	
	// in place union operator
	const Set& operator+=(const Set& b);
	
	// in place minus operator
	const Set& operator-=(const Set& b);
	
	// Removes Element from the set
	const Set& operator-=(const T& elem);
	
	// Adds single Element to the set
	const Set<T>& operator+=(const T& elem);
	
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
Set<T>::Set(const std::string& s){
	std::istringstream in(s);
	T t;
	while (in >> t){
		tab.push_back(t);
	}
}


template <class T>
bool Set<T>::isIncluded(const Set<T>& b) const{
	bool bIncluded = true;
	int i = 0, j=0;
	while (bIncluded && j<b.tab.size()){
		while (i<tab.size() && tab[i] < b.tab[j])
			++i;
		if (i==tab.size() || tab[i] > b.tab[j])
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


inline std::ostream& operator<<(std::ostream& out, const Set<Attribute>& a){
	for (int i = 0; i < a.tab.size() - 1; ++i){
		out << a.tab[i] << " ";
	}
	out << a.tab.back();
	
	return out;
}


template <class T>
const Set<T>& Set<T>::operator-=(const Set<T>& b){
	std::vector<T> out(tab.size() + b.tab.size());
	auto it = set_difference(tab.begin(), tab.end(), b.tab.begin(), b.tab.end(), out.begin());
	out.resize(it-out.begin());
	tab.swap(out);
	
	return *this;
}

//TODO: Change this when going to lists (replace by reverse iteration)
template <class T>
const Set<T>& Set<T>::operator-=(const T& elem){
	auto first = tab.begin();
	first = std::lower_bound(first,tab.end(),elem);
	if (first!=tab.end() && !(elem<*first)){
		tab.erase(first);
	}
}


template <class T>
const Set<T>& Set<T>::operator+=(const T& elem){
	auto first = tab.begin();
	first = std::lower_bound(first,tab.end(),elem);
	if (first == tab.end() || (elem < *first)){
		tab.insert(first, elem);
	}
	return *this;
}

typedef Set<FD> FDSet ;
typedef Set<Attribute> AttSet;

#endif /* Set_hpp */










