#include "test.h"
#include "salsa20.h"
#include <iostream>

using namespace std;

bool test_lrot(){
	return Salsa20::lrot(0xc0a8787e, 5) == 0x150f0fd8;
}

bool test_quaterround(){
	vector< vector<uint32_t>> y{ 
			{0x00000000, 0x00000000, 0x00000000, 0x00000000},
			{0x00000001, 0x00000000, 0x00000000, 0x00000000},
			{0x00000000, 0x00000001, 0x00000000, 0x00000000},
			{0x00000000, 0x00000000, 0x00000001, 0x00000000},
			{0x00000000, 0x00000000, 0x00000000, 0x00000001},
			{0xe7e8c006, 0xc4f9417d, 0x6479b4b2, 0x68c67137},
			{0xd3917c5b, 0x55f1c407, 0x52a58a7a, 0x8f887a3b}
		},
		z{
			vector<uint32_t>(4),
			vector<uint32_t>(4),
			vector<uint32_t>(4),
			vector<uint32_t>(4),
			vector<uint32_t>(4),
			vector<uint32_t>(4),
			vector<uint32_t>(4),
		},
		r{
			{0x00000000, 0x00000000, 0x00000000, 0x00000000},
			{0x08008145, 0x00000080, 0x00010200, 0x20500000},
			{0x88000100, 0x00000001, 0x00000200, 0x00402000},
			{0x80040000, 0x00000000, 0x00000001, 0x00002000},
			{0x00048044, 0x00000080, 0x00010000, 0x20100001},
			{0xe876d72b, 0x9361dfd5, 0xf1460244, 0x948541a3},
			{0x3e2f308c, 0xd90a8f36, 0x6ab2a923, 0x2883524c},
		};
		
	success = true;
	for(int i =0; i< 7; i++){
		quateround(y[i], z[i]);
		if(z[i] != r [i]){
			success = false;
			cout << "Entry : " << y[i] << endl << "Output : " << z[i] << 
			endl << "Expected : " << r;
		}
	}
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
