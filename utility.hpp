#ifndef UTILITY_HPP
#define UTILITY_HPP

#include<iostream>

template<typename T>
ostream& operator<<(ostream& os, const vector<T> t){
	os << "[ ";
	for(auto i: t){
		os << i << " ";
	}
	os << "]";
	return os;
}

template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U> t){
	os << "( " << t.first << ", " << t.second << " )";
	return os;
}

template<typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b){
	vector<T> r;
	r.insert(r.end(), a.begin(), a.end());
	r.insert(r.end(), b.begin(), b.end());
	return r;
}


#endif
