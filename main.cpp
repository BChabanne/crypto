#include<iostream>
#include "test.h"

using namespace std;

int main(){
	bool success = test();
	if(success){
		cout << "All tests completed" << endl;
	} else {
		cout << "Unit test failed" << endl;
	}
	return 0;
}
