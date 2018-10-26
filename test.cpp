#include "test.h"
#include "salsa20.h"
#include <iostream>

using namespace std;

bool test_lrot(){
	return Salsa20::lrot(0xc0a8787e, 5) == 0x150f0fd8;
}

bool test_quaterround(){

	return false;
}

bool test_rowround(){
	return false;
}

bool test_columnround(){
	return false;
}

bool test_doubleround(){
	return false;
}

bool test_littleendian(){
	return false;
}

bool test_littleendian_inv(){
	return false;
}

bool test_Salsa20(){
	return false;
}

bool test_Salsa20Exp(){
	return false;
}

bool test_Salsa20Encrypt(){
	return false;
}

bool test(){
	bool success = true;
	if(!test_lrot()){
		success = false;
		cout << "Test of lrot didn't succeded" << endl;
	}
	if(!test_quaterround()){
		success = false;
		cout << "Test of quaterround didn't succeded" << endl;
	}
	if(!test_rowround()){
		success = false;
		cout << "Test of rowround didn't succeded" << endl;
	}
	if(!test_columnround()){
		success = false;
		cout << "Test of columnround didn't succeded" << endl;
	}
	if(!test_doubleround()){
		success = false;
		cout << "Test of doubleround didn't succeded" << endl;
	}
	if(!test_littleendian()){
		success = false;
		cout << "Test of littleendian didn't succeded" << endl;
	}
	if(!test_littleendian_inv()){
		success = false;
		cout << "Test of littleendian_inv didn't succeded" << endl;
	}
	if(!test_Salsa20()){
		success = false;
		cout << "Test of Salsa20 didn't succeded" << endl;
	}
	if(!test_Salsa20Exp()){
		success = false;
		cout << "Test of Salsa20Exp didn't succeded" << endl;
	}
	if(!test_Salsa20Encrypt()){
		success = false;
		cout << "Test of Salsa20Encrypt didn't succeded" << endl;
	}
	
	if(success){
		cout << "All tests succeded" << endl;
	}
	return success;	
}
