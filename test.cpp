#include "test.h"
#include "salsa20.h"
#include <iostream>

using namespace std;

bool test_lrot(){
	return Salsa20::lrot(0xc0a8787e, 5) == 0x150f0fd8;
}

bool test(){
	bool success = true;
	if(!test_lrot()){
		success = false;
		cout << "Test of lrot didn't succeded" << endl;
	}
	
	if(success){
		cout << "All tests succeded" << endl;
	}
	return success;	
}
