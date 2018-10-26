#ifndef SALSA20
#define SALSA20

 #include <stdint.h>
#include<vector>

using namespace std;
#include "salsa20.h"
#include<vector>

namespace Salsa20 {
	uint32_t lrot(uint32_t x, uint32_t c);
	/*lrot a left rotation of c bit from x*/
	
	vector<uint32_t> quaterround(const vector<uint32_t>& y);
	/*Calculate value of the 4-uple y applying quaterround as defined in TP 
	and save result in z*/
	
	vector<uint32_t> rowround(const vector<uint32_t>& y);
	/*Calculate value of the 16-tuple y applying rowround as defined in TP
	and save result in z*/
	
	vector<uint32_t> columnround(const vector<uint32_t>& y);
	/*Calculate value of the 16-tuple y applying columnround as defined in TP
	and save result in z*/
	
	vector<uint32_t> doubleround(const vector<uint32_t>& x);
	/*Calculate composition of rowround and columnround and save result in z
		x must be a 16-tuple
	*/ 
	
	uint32_t littleendian(const vector<unsigned char>& b);
	/*Return the value of littleendian of the 4-tuple b as described in TP*/
	
	vector<unsigned char> littleendian_inv(uint32_t x);
	/*Return the littleendian composants of x in b*/
	
	vector<unsigned char> Salsa20(const vector<unsigned char>& x);
	/*Salsa20 algorithm as defined in TP*/
	
	vector<unsigned char> Salsa20Exp(const vector<unsigned char>& k, const vector<unsigned char>& v);
	/*Return Slasa20exp as defined in TP depending on key k and initializing 
	vector v*/
	
	vector<unsigned char> Salsa20Encrypt(const vector<unsigned char>& k, const vector<unsigned char>& n, const vector<unsigned char>& m);
	/*Return Salsa20Encrypt as descripbed in TP*/
}
	
#endif
