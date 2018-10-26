#ifndef SALSA20
#define SALSA20

 #include <stdint.h>
#include<vector>

using namespace std;

namespace Salsa20 {
	uint32_t lrot(uint32_t x, uint32_t c);
	/*lrot a left rotation of c bit from x*/
	
	void quaterround(const vector<uint32_t&>& y, vector<uint32_t&>& z);
	/*Calculate value of the 4-uple y applying quaterround as defined in TP 
	and save result in z*/
	
	void rowround(const vector<uint32_t&>& y, vector<uint32_t&> & z);
	/*Calculate value of the 16-tuple y applying rowround as defined in TP
	and save result in z*/
	
	void columnround(const vector<uint32_t&>& y, vector<uint32_t&>& z);
	/*Calculate value of the 16-tuple y applying columnround as defined in TP
	and save result in z*/
	
	void doubleround(const vector<uint32_t&>& x, vector<uint32_t&>& z);
	/*Calculate composition of rowround and columnround and save result in z
		x must be a 16-tuple
	*/ 
	
	uint32_t littleendian(const vector<char&>& b);
	/*Return the value of littleendian of the 4-tuple b as described in TP*/
	
	void littleendian_inv(uint32_t x, vector<char&>& b);
	/*Return the littleendian composants of x in b*/
	
	vector<char> Salsa20(const vector<char>& x);
	/*Salsa20 algorithm as defined in TP*/
	
	vector<char> Salsa20Exp(const vector<char>& k, const vector<char>& v);
	/*Return Slasa20exp as defined in TP depending on key k and initializing 
	vector v*/
	
	vector<char> Salsa20Encrypt(const vector<char>& k, const vector<char>& n, const vector<char>& m);
	/*Return Salsa20Encrypt as descripbed in TP*/
}
#endif
