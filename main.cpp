#include<iostream>
#include "test.h"

using namespace std;

int main(){
	/*This program will simply launch all test implemented for
	the Salsa20 method.
	It will print on the console if it's succeded or not
	We could change the programm a little bit use cerr if test failed and return a code different than 0 if this programm was supposed to be used in bash script
	*/
	bool success = test();
	if(success){
		cout << "All tests completed" << endl;
	} else {
		cout << "Unit test failed" << endl;
	}
	return 0;
}
