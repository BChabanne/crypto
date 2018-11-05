#ifndef UTILITY_HPP
#define UTILITY_HPP

#include<iostream>

template<typename T>
ostream& operator<<(ostream& os, const vector<T> t){
	/*Operator for printing a vector with the form [ a b c ]*/
	os << "[ ";
	for(auto i: t){
		os << i << " ";
	}
	os << "]";
	return os;
}

template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U> t){
	/*Operator for printing a pair under the form (a, b)*/
	os << "( " << t.first << ", " << t.second << " )";
	return os;
}

template<typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b){
	/*use operator + for vector to concatenate 2 vectors*/
	vector<T> r;
	r.insert(r.end(), a.begin(), a.end());
	r.insert(r.end(), b.begin(), b.end());
	return r;
}


#endif
