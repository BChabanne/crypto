#include <iostream>
#include <utility>
#include <stdexcept>
#include "test.h"
#include "salsa20.h"
#include "utility.hpp"

using namespace std;

template<typename T, typename U>
static void print_data(const T& entry, const U& output, const U& result){
	/*This function is used when there is an error between entry and output. It's just a simple visualization*/
	cout << "Entry    : " << entry << endl;
	cout << "Output   : " << output << endl ;
	cout << "Expected : " << result << endl;
}

static bool test_lrot(){
	/*Test function with entry given in TP*/
	uint32_t y = 0xc0a8787e,
		z = Salsa20::lrot(y, 5), 
		r =0x150f0fd8;
	if(z != r){
		print_data(pair<uint32_t, int>(y, 5),z,r);
	}
	return z == r;
}

static bool test_quaterround(){
	/*Test function with entry given in TP*/
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
		
	bool success = true;
	for(int i =0; i< 7; i++){
		z[i] = Salsa20::quaterround(y[i]);
		if(z[i] != r[i]){
			success = false;
			print_data(y[i],z[i],r[i]);
		}
	}
	return success;
}

static bool test_rowround(){
	/*Test function with entry given in TP*/
	vector<uint32_t> y1{0x00000001, 0x00000000, 0x00000000, 0x00000000, 
		0x00000001, 0x00000000, 0x00000000, 0x00000000, 
		0x00000001, 0x00000000, 0x00000000, 0x00000000, 
		0x00000001, 0x00000000, 0x00000000, 0x00000000
		}, 
		y2 {0x08521bd6, 0x1fe88837, 0xbb2aa576, 0x3aa26365, 
		0xc54c6a5b, 0x2fc74c2f, 0x6dd39cc3, 0xda0a64f6, 
		0x90a2f23d, 0x067f95a6, 0x06b35f61, 0x41e4732e, 
		0xe859c100, 0xea4d84b7, 0x0f619bff, 0xbc6e965a
		},
		z1{0x08008145, 0x00000080, 0x00010200, 0x20500000, 
		0x20100001, 0x00048044, 0x00000080, 0x00010000, 
		0x00000001, 0x00002000, 0x80040000, 0x00000000, 
		0x00000001, 0x00000200, 0x00402000, 0x88000100
		},
		z2{0xa890d39d, 0x65d71596, 0xe9487daa, 0xc8ca6a86, 
		0x949d2192, 0x764b7754, 0xe408d9b9, 0x7a41b4d1, 
		0x3402e183, 0x3c3af432, 0x50669f96, 0xd89ef0a8, 
		0x0040ede5, 0xb545fbce, 0xd257ed4f, 0x1818882d
		}, 
		r1(16), r2(16);
		
	bool success = true;
	
	r1 = Salsa20::rowround(y1);
	if(r1 != z1){
		print_data(y1, r1, z1);
		success = false;
	}
	
	r2 = Salsa20::rowround(y2);
	if(r2 != z2){
		print_data(y2, r2, z2);
		success = false;
	}
	
	return success;
}

static bool test_columnround(){
	/*Test function with entry given in TP*/
	vector<uint32_t> y1{0x00000001, 0x00000000, 0x00000000, 0x00000000, 
	0x00000001, 0x00000000, 0x00000000, 0x00000000, 
	0x00000001, 0x00000000, 0x00000000, 0x00000000, 
	0x00000001, 0x00000000, 0x00000000, 0x00000000
	},
	y2{0x08521bd6, 0x1fe88837, 0xbb2aa576, 0x3aa26365, 
	0xc54c6a5b, 0x2fc74c2f, 0x6dd39cc3, 0xda0a64f6, 
	0x90a2f23d, 0x067f95a6, 0x06b35f61, 0x41e4732e, 
	0xe859c100, 0xea4d84b7, 0x0f619bff, 0xbc6e965a
	},
	z1{0x10090288, 0x00000000, 0x00000000, 0x00000000, 
	0x00000101, 0x00000000, 0x00000000, 0x00000000, 
	0x00020401, 0x00000000, 0x00000000, 0x00000000, 
	0x40a04001, 0x00000000, 0x00000000, 0x00000000
	},
	z2{0x8c9d190a, 0xce8e4c90, 0x1ef8e9d3, 0x1326a71a, 
	0x90a20123, 0xead3c4f3, 0x63a091a0, 0xf0708d69, 
	0x789b010c, 0xd195a681, 0xeb7d5504, 0xa774135c, 
	0x481c2027, 0x53a8e4b5, 0x4c1f89c5, 0x3f78c9c8
	},
	r1(4), r2(4);

	bool success = true;
	
	r1 = Salsa20::columnround(y1);
	if(r1 != z1){
		print_data(y1, r1, z1);
		success = false;
	}
	
	r2 = Salsa20::columnround(y2);
	if(r2 != z2){
		print_data(y2, r2, z2);
		success = false;
	}
	
	return success;
}

static bool test_doubleround(){
	/*Test function with entry given in TP*/
	vector<uint32_t> y1{0x00000001, 0x00000000, 0x00000000, 0x00000000, 
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 
	0x00000000, 0x00000000, 0x00000000, 0x00000000
	},
	y2{0xde501066, 0x6f9eb8f7, 0xe4fbbd9b, 0x454e3f57, 
	0xb75540d3, 0x43e93a4c, 0x3a6f2aa0, 0x726d6b36, 
	0x9243f484, 0x9145d1e8, 0x4fa9d247, 0xdc8dee11, 
	0x054bf545, 0x254dd653, 0xd9421b6d, 0x67b276c1
	},
	z1{0x8186a22d, 0x0040a284, 0x82479210, 0x06929051, 
	0x08000090, 0x02402200, 0x00004000, 0x00800000, 
	0x00010200, 0x20400000, 0x08008104, 0x00000000, 
	0x20500000, 0xa0000040, 0x0008180a, 0x612a8020
	},
	z2{0xccaaf672, 0x23d960f7, 0x9153e63a, 0xcd9a60d0, 
	0x50440492, 0xf07cad19, 0xae344aa0, 0xdf4cfdfc, 
	0xca531c29, 0x8e7943db, 0xac1680cd, 0xd503ca00, 
	0xa74b2ad6, 0xbc331c5c, 0x1dda24c7, 0xee928277
	},
	r1(4), r2(4);

	bool success = true;
	
	r1 = Salsa20::doubleround(y1);
	if(r1 != z1){
		print_data(y1, r1, z1);
		success = false;
	}
	
	r2 = Salsa20::doubleround(y2);
	if(r2 != z2){
		print_data(y2, r2, z2);
		success = false;
	}
	
	return success;
}

static bool test_littleendian(){
	/*Test function with entry given in TP*/
	vector< vector<unsigned char> > y{
		{0, 0, 0, 0},
		{86, 75, 30, 9},
		{255, 255, 255, 250}
	};
	vector<uint32_t> z(3), r{0x00000000, 0x091e4b56, 0xfaffffff};
	
	bool success = true;
	for(int i = 0; i< 3; i++){
		z[i] = Salsa20::littleendian(y[i]);
		if(z[i] != r[i]){
			print_data(y[i], r[i], z[i]);
			success = false;
		}
	}
	return success;
}

static bool test_littleendian_inv(){
	/*Test function with entry given in TP*/
	vector<uint32_t> y{0x00000000, 0x091e4b56, 0xfaffffff};
	vector< vector<unsigned char> > z(3), r{
		{0, 0, 0, 0},
		{86, 75, 30, 9},
		{255, 255, 255, 250}
	};
	
	bool success = true;
	for(int i=0; i< 3; i++){
		z[i] = Salsa20::littleendian_inv(y[i]);
		if(z[i] != r[i]){
			print_data(y[i], r[i], z[i]);
			success = false;
		}
	}

	return success;
}

static bool test_Salsa20(){
	/*Test function with entry given in TP*/
	vector<vector<unsigned char> > y{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{211,159, 13,115, 76, 55, 82,183, 3,117,222, 37,191,187,234,136,
		 49,237,179, 48, 1,106,178,219,175,199,166, 48, 86, 16,179,207,
		 31,240, 32, 63, 15, 83, 93,161,116,147, 48,113,238, 55,204, 36,
		 79,201,235, 79, 3, 81,156, 47,203, 26,244,243, 88,118,104, 54},
		{88,118,104, 54, 79,201,235, 79, 3, 81,156, 47,203, 26,244,243,
		 191,187,234,136,211,159, 13,115, 76, 55, 82,183, 3,117,222, 37, 
		 86, 16,179,207, 49,237,179, 48, 1,106,178,219,175,199,166, 48,
		 238, 55,204, 36, 31,240, 32, 63, 15, 83, 93,161,116,147, 48,113},
	},
	z(3),
	r{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{109, 42,178,168,156,240,248,238,168,196,190,203, 26,110,170,154, 
		 29, 29,150, 26,150, 30,235,249,190,163,251, 48, 69,144, 51, 57,
		 118, 40,152,157,180, 57, 27, 94,107, 42,236, 35, 27,111,114,114,
		 219,236,232,135,111,155,110, 18, 24,232, 95,158,179, 19, 48,202
		},
		{179, 19, 48,202,219,236,232,135,111,155,110, 18, 24,232, 95,158,
		 26,110,170,154,109, 42,178,168,156,240,248,238,168,196,190,203,
		 69,144, 51, 57, 29, 29,150, 26,150, 30,235,249,190,163,251, 48,
		  27,111,114,114,118, 40,152,157,180, 57, 27, 94,107, 42,236, 35
		}
	};
	
	bool success = true;
	for(int i=0; i< 3; i++){
		z[i] = Salsa20::Salsa20(y[i]);
		if(z[i] != r[i]){
			print_data(y[i], r[i], z[i]);
			success = false;
		}
	}

	return success;
}

static bool test_Salsa20Exp(){
	/*Test function with entry given in TP*/
	vector<unsigned char> k0{1,2,3,4,5,6,7,8, 9,10,11,12,13,14,15,16}, 
		k1{201,202,203,204,205,206,207,208, 209,210,211,212,213,214,215,216}, 
		v{101,102,103,104,105,106,107,108, 109,110,111,112,113,114,115,116},
		z1, z2,
		r1{69, 37, 68, 39, 41, 15,107,193,255,139,122, 6,170,233,217, 98, 89,144,182,106, 21, 51,200, 65,239, 49,222, 34,215,114, 40,126, 104,197, 7,225,197,153, 31, 2,102, 78, 76,176, 84,245,246,184, 177,160,133,130, 6, 72,149,119,192,195,132,236,234,103,246, 74
		},
		r2{
		39,173, 46,248, 30,200, 82, 17, 48, 67,254,239, 37, 18, 13,247, 241,200, 61,144, 10, 55, 50,185, 6, 47,246,253,143, 86,187,225, 134, 85,110,246,161,163, 43,235,231, 94,171, 51,145,214,112, 29, 14,232, 5, 16,151,140,183,141,171, 9,122,181,104,182,177,193
		};
		
	bool success = true;
	
	z1 = Salsa20::Salsa20Exp( k0 + k1, v);
	if(z1 != r1){
		cout << "Salsa20Exp test 1 failed" << endl;
		success = false;
	}
	
	z2 = Salsa20::Salsa20Exp( k0, v);
	if(z2 != r2){
		cout << "Salsa20Exp test 2 failed" << endl;
		success = false;
	}

	return success;
}

static bool test_Salsa20Encrypt(){
	/*Test function with entry given in TP*/
	vector<unsigned char> k0{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
		k1{201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216},
		n{101,102,103,104,105,106,107,108},
		m{83,111,117,118,101,110,116,44,32,112,111,117,114,32,115,39,97,109,117,115,101,114,44,32,108,101,115,32,104,111,109,109,101,115,32,100,39,101,113,117,105,112,97,103,101,13,10,80,114,101,110,110,101,110,116,32,100,101,115,32,97,108,98,97,116,114,111,115,44,32,118,97,115,116,101,115,32,111,105,115,101,97,117,120,32,100,101,115,32,109,101,114,115,44,13,10,81,117,105,32,115,117,105,118,101,110,116,44,32,105,110,100,111,108,101,110,116,115,32,99,111,109,112,97,103,110,111,110,115,32,100,101,32,118,111,121,97,103,101,44,13,10,76,101,32,110,97,118,105,114,101,32,103,108,105,115,115,97,110,116,32,115,117,114,32,108,101,115,32,103,111,117,102,102,114,101,115,32,97,109,101,114,115,46,13,10,13,10,65,32,112,101,105,110,101,32,108,101,115,32,111,110,116,45,105,108,115,32,100,101,112,111,115,101,115,32,115,117,114,32,108,101,115,32,112,108,97,110,99,104,101,115,44,13,10,81,117,101,32,99,101,115,32,114,111,105,115,32,100,101,32,108,39,97,122,117,114,44,32,109,97,108,97,100,114,111,105,116,115,32,101,116,32,104,111,110,116,101,117,120,44,13,10,76,97,105,115,115,101,110,116,32,112,105,116,101,117,115,101,109,101,110,116,32,108,101,117,114,115,32,103,114,97,110,100,101,115,32,97,105,108,101,115,32,98,108,97,110,99,104,101,115,13,10,67,111,109,109,101,32,100,101,115,32,97,118,105,114,111,110,115,32,116,114,97,111,110,101,114,32,97,32,99,111,116,101,32,100,39,101,117,120,46,13,10,13,10,67,101,32,118,111,121,97,103,101,117,114,32,97,105,108,101,44,32,99,111,109,109,101,32,105,108,32,101,115,116,32,103,97,117,99,104,101,32,101,116,32,118,101,117,108,101,32,33,13,10,76,117,105,44,32,110,97,103,117,101,114,101,32,115,105,32,98,101,97,117,44,32,113,117,39,105,108,32,101,115,116,32,99,111,109,105,113,117,101,32,101,116,32,108,97,105,100,32,33,13,10,76,39,117,110,32,97,103,97,99,101,32,115,111,110,32,98,101,99,32,97,118,101,99,32,117,110,32,98,114,117,108,101,45,103,117,101,117,108,101,44,13,10,76,39,97,117,116,114,101,32,109,105,109,101,44,32,101,110,32,98,111,105,116,97,110,116,44,32,108,39,105,110,102,105,114,109,101,32,113,117,105,32,118,111,108,97,105,116,32,33,13,10,13,10,76,101,32,80,111,101,116,101,32,101,115,116,32,115,101,109,98,108,97,98,108,101,32,97,117,32,112,114,105,110,99,101,32,100,101,115,32,110,117,101,101,115,13,10,81,117,105,32,104,97,110,116,101,32,108,97,32,116,101,109,112,101,116,101,32,101,116,32,115,101,32,114,105,116,32,100,101,32,108,39,97,114,99,104,101,114,32,59,13,10,69,120,105,108,101,32,115,117,114,32,108,101,32,115,111,108,32,97,117,32,109,105,108,105,101,117,32,100,101,115,32,104,117,101,101,115,44,13,10,83,101,115,32,97,105,108,101,115,32,100,101,32,103,101,97,110,116,32,108,39,101,109,112,101,99,104,101,110,116,32,100,101,32,109,97,114,99,104,101,114,46,13,10,13,10
		
		},
		z1, z2,
		r1{ 243, 244, 2, 111, 71, 92, 108, 132, 219, 213, 204, 72, 205, 33, 214, 31, 98, 234, 248, 73, 163, 111, 31, 219, 82, 159, 31, 80, 68, 250, 190, 224, 40, 81, 177, 171, 108, 191, 33, 11, 82, 247, 217, 125, 119, 214, 47, 252, 9, 10, 239, 66, 206, 19, 218, 193, 31, 136, 78, 168, 201, 195, 217, 245, 139, 115, 180, 45, 163, 185, 110, 43, 146, 168, 163, 169, 109, 49, 53, 234, 88, 159, 63, 133, 197, 66, 248, 239, 115, 236, 10, 46, 59, 13, 122, 107, 183, 181,
253, 215, 145, 81, 192, 55, 244, 16, 67, 16, 149, 204, 93, 212, 37, 191, 109, 233, 221, 239, 99, 136, 182, 82, 98, 55, 2, 10, 79, 226, 74, 179, 199, 164, 140, 68, 51, 38, 238, 46, 169, 238, 149, 253, 245, 147, 105, 237, 130, 71, 98, 41, 183, 59, 19, 180, 192, 144, 7, 36, 40, 105, 83, 112, 189, 168, 217, 29, 70, 65, 245, 139, 29, 4, 223, 174, 11, 117, 43, 9, 23, 112, 97, 138, 176, 248, 105, 117, 136, 121, 61, 176, 88, 218, 32, 219, 139, 170, 167, 224, 49, 210, 39, 98, 115, 196, 62, 16,
159, 52, 197, 93, 194, 132, 184, 130, 255, 139, 223, 145, 115, 243, 72, 202, 180, 135, 141, 149, 178, 221, 172, 58, 137, 218, 145, 19, 190, 195, 53, 14, 139, 155, 250, 99, 73, 31, 118, 109, 61, 6, 253, 206, 93, 85, 6, 237, 65, 182, 173, 195, 47, 85, 135, 95, 235, 206, 22, 190, 93, 208, 251, 253, 68, 78, 217, 172, 127, 246, 14, 38, 0, 107, 217, 40, 108, 114, 45, 119, 110, 199, 215, 132, 125, 111, 224, 149, 95, 37, 151, 204, 0, 23, 54, 40, 244, 239, 73, 120, 200, 189, 68, 108, 10, 204,
148, 82, 55, 25, 92, 193, 4, 59, 194, 114, 207, 62, 167, 189, 59, 175, 115, 218, 169, 237, 173, 210, 221, 27, 201, 90, 1, 9, 208, 155, 10, 119, 19, 173, 149, 155, 46, 136, 214, 195, 70, 127, 110, 168, 117, 80, 208, 253, 24, 230, 255, 158, 187, 76, 104, 135, 225, 132, 132, 120, 14, 237, 175, 103, 255, 74, 125, 205, 174, 238, 17, 148, 106, 98, 70, 146, 100, 9, 188, 61, 165, 177, 88, 68, 220, 226, 62, 228, 83, 14, 128, 254, 123, 92, 231, 250, 248, 73, 132, 58, 190, 63, 74, 150, 81,
66, 7, 255, 33, 96, 3, 236, 208, 180, 217, 39, 177, 21, 241, 39, 198, 74, 91, 183, 76, 16, 133, 162, 249, 232, 171, 255, 84, 254, 155, 72, 143, 208, 61, 252, 2, 109, 56, 217, 37, 38, 135, 232, 20, 161, 206, 62, 7, 119, 25, 207, 25, 228, 238, 226, 184, 202, 80, 72, 49, 157, 93, 76, 135, 139, 18, 22, 177, 64, 23, 114, 129, 21, 66, 94, 32, 40, 138, 193, 83, 252, 130, 15, 75, 0, 67, 86, 112, 222, 99, 105, 78, 132, 111, 124, 231, 123, 131, 125, 92, 46, 37, 252, 247, 72, 49, 155, 255, 25, 79,
62, 15, 226, 55, 213, 237, 244, 202, 90, 230, 26, 114, 148, 171, 242, 4, 162, 54, 235, 49, 89, 196, 15, 108, 161, 70, 190, 219, 80, 202, 88, 146, 223, 250, 128, 0, 235, 47, 167, 86, 44, 235, 215, 7, 78, 184, 91, 194, 23, 217, 49, 169, 237, 156, 196, 37, 172, 6, 37, 99, 249, 86, 114, 135, 171, 138, 170, 165, 219, 76, 240, 36, 248, 37, 72, 176, 138, 42, 82, 102, 34, 105, 219, 226, 126, 180, 85, 166, 211, 254, 82, 89, 76, 236, 33, 109, 48, 95, 135, 143, 237, 53, 244, 129, 155, 16, 53,
31, 97, 171, 23, 101, 210, 95, 43, 208, 69, 164, 89, 61, 105, 194, 47, 243, 91, 225, 79, 73, 190, 194, 160, 74, 80, 119, 121, 248, 246, 17, 208, 227, 56, 99, 203, 29, 16, 116, 201, 142, 107, 109, 92, 87, 115, 31, 242, 30, 129, 0, 39, 109, 32, 244, 160, 69, 114, 2, 56, 251, 178, 104, 68, 17, 89, 42, 173, 174, 237, 9, 142, 227, 102, 113, 172, 123, 255, 37, 38, 182, 192, 136, 163, 251, 144, 20, 217, 216, 149, 236, 57, 253, 42, 238, 168, 251, 192, 236, 26, 131, 153, 71, 135, 196, 19, 235, 69,
7, 98, 195, 157, 202
		},
		r2{153, 134, 113, 196, 18, 195, 220, 127, 59, 92, 180, 242, 107, 54, 229, 191, 185, 211, 165, 179, 104, 94, 120, 178, 89, 96, 37, 241, 229, 72, 75, 125, 157, 55, 205, 173, 4, 196, 230, 179, 109, 224, 85, 78, 105, 158, 6, 83, 88, 41, 184, 98, 12, 113, 60, 39, 245, 180, 124, 134, 9, 232, 99, 117, 220, 90, 114, 77, 0, 64, 175, 250, 29, 29, 2, 249, 227, 136, 102, 214, 5, 158, 183, 154, 29, 170, 244, 124, 206, 182, 17, 66, 90, 216, 65, 210, 198, 250, 241, 228, 177, 88,
142, 45, 83, 68, 126, 193, 72, 2, 236, 170, 148, 143, 228, 80, 93, 108, 228, 13, 38, 253, 223, 216, 6, 111, 146, 219, 243, 125, 105, 88, 43, 139, 251, 187, 201, 74, 201, 23, 146, 250, 229, 28, 212, 141, 29, 31, 137, 7, 190, 42, 109, 160, 160, 56, 222, 123, 240, 137, 206, 180, 99, 25, 116, 2, 218, 111, 140, 198, 189, 248, 128, 50, 142, 251, 133, 166, 131, 40, 236, 181, 158, 218, 190, 124, 103, 255, 16, 157, 70, 43, 50, 126, 149, 17, 144, 219, 195, 181, 172, 50, 223, 175, 181, 35, 54,
154, 178, 0, 248, 64, 149, 230, 231, 226, 43, 220, 211, 220, 211, 216, 211, 101, 244, 47, 71, 69, 88, 176, 233, 185, 236, 202, 99, 216, 137, 178, 202, 114, 196, 46, 107, 129, 87, 84, 185, 148, 35, 6, 83, 224, 95, 6, 1, 195, 131, 177, 13, 108, 136, 209, 43, 178, 26, 62, 120, 127, 90, 15, 100, 202, 86, 229, 184, 38, 208, 185, 51, 46, 114, 104, 103, 118, 182, 251, 234, 239, 234, 123, 44, 132, 173, 7, 166, 97, 254, 101, 207, 229, 223, 73, 199, 223, 2, 1, 58, 150, 79, 195, 167, 107, 61, 234,
40, 221, 114, 107, 214, 0, 142, 35, 118, 134, 21, 189, 25, 179, 81, 120, 165, 231, 224, 9, 216, 169, 155, 186, 53, 155, 140, 7, 242, 132, 137, 242, 212, 129, 51, 227, 101, 28, 92, 168, 218, 202, 98, 230, 71, 4, 116, 252, 228, 134, 159, 253, 19, 66, 12, 145, 165, 31, 66, 85, 104, 69, 70, 75, 126, 166, 248, 111, 124, 56, 60, 88, 19, 32, 246, 153, 162, 131, 158, 209, 238, 166, 101, 201, 17, 104, 253, 42, 107, 244, 188, 115, 160, 196, 34, 134, 212, 9, 207, 3, 39, 164, 121, 67, 111, 5, 243,
20, 249, 161, 1, 72, 187, 214, 70, 15, 75, 208, 21, 42, 29, 48, 148, 173, 73, 148, 8, 190, 249, 120, 253, 7, 83, 112, 100, 214, 107, 107, 240, 53, 64, 170, 33, 45, 94, 27, 17, 198, 215, 118, 89, 35, 22, 37, 93, 162, 85, 238, 65, 44, 166, 251, 148, 63, 161, 254, 210, 253, 107, 195, 239, 100, 67, 171, 144, 108, 198, 105, 220, 52, 117, 47, 23, 168, 157, 148, 222, 206, 13, 110, 84, 53, 76, 4, 175, 239, 51, 37, 146, 50, 115, 106, 92, 197, 201, 159, 229, 168, 57, 98, 203, 187, 242, 188, 12,
4, 148, 169, 223, 188, 43, 227, 127, 193, 218, 254, 43, 252, 44, 216, 120, 86, 26, 238, 116, 224, 62, 98, 195, 231, 182, 10, 130, 29, 8, 133, 50, 146, 122, 53, 79, 138, 253, 17, 195, 231, 117, 79, 136, 199, 131, 52, 77, 242, 169, 63, 48, 142, 116, 94, 186, 115, 68, 150, 186, 96, 183, 21, 48, 187, 48, 242, 85, 17, 49, 129, 123, 227, 81, 98, 102, 199, 86, 183, 138, 110, 114, 54, 243, 204, 14, 193, 125, 113, 167, 82, 208, 26, 252, 230, 60, 110, 58, 169, 90, 103, 39, 100, 255, 101, 127, 122,
144, 181, 89, 245, 144, 88, 157, 251, 112, 13, 130, 248, 13, 71, 157, 142, 6, 245, 69, 204, 107, 189, 27, 100, 221, 94, 227, 105, 136, 176, 213, 218, 108, 229, 247, 192, 24, 148, 166, 15, 143, 238, 164, 42, 60, 26, 135, 11, 207, 163, 67, 189, 194, 17, 239, 94, 29, 216, 102, 50, 215, 25, 41, 46, 185, 52, 109, 139, 156, 32, 133, 2, 44, 92, 220, 207, 22, 24, 255, 137, 208, 0, 198, 15, 22, 186, 209, 241, 47, 1, 102, 190, 199, 221, 134, 207, 175, 172, 107, 79, 26, 246, 97, 222, 204, 116, 76,
133, 247, 128, 110
	};

	bool success = true;
	
	z1 = Salsa20::Salsa20Encrypt( k0 + k1, n, m);
	if(z1 != r1){
		cout << "First encryption didn't work" << endl;
		success = false;
	}
	
	z2 = Salsa20::Salsa20Encrypt(k0, n, m);
	if(z2 != r2){
		cout << "Second encryption didn't work" << endl;
		success = false;
		}
	return success;
}

static bool test_function( bool (*f)(), const string& name){
	/*Test function with entry given in TP*/
	if(!f()){
		cout << "Test of " << name << " didn't succeed" << endl;
		return false;
	}
	return true;
}

bool test(){
	bool success = true;
	
	/*Test apply on all these functions*/
	vector<pair<string, bool(*)()> > functions{
		{"test_lrot", test_lrot},
		{"test_quaterround", test_quaterround},
		{"test_rowround" , test_rowround},
		{"test_columnround", test_columnround},
		{"test_doubleround", test_doubleround},
		{"test_littleendian", test_littleendian},
		{"test_littleendian_inv", test_littleendian_inv},
		{"test_Salsa20", test_Salsa20},
		{"test_Salsa20Exp", test_Salsa20Exp},
		{"test_Salsa20Encrypt", test_Salsa20Encrypt}
	};
	
	for(auto f : functions){
		/*Test all functions, and will return false if at least
		one of these test failed*/
		success = success && test_function(f.second, f.first);
	}

	return success;	
}
