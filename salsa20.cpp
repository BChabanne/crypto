#include "salsa20.h"
#include<vector>
#include<stdexcept>
#include "utility.hpp"

uint32_t Salsa20::lrot(uint32_t x, uint32_t c){
  return (x << c)|(x >> (8*sizeof(uint32_t) - c)); 
}

vector<uint32_t> Salsa20::quaterround(const vector<uint32_t>& y) {
	if(y.size() != 4){
			throw invalid_argument("Argument vector should be of size 4");
	}
	vector<uint32_t> z(4);
	z[1] = y[1] ^ lrot(y[0] + y[3],7);
	z[2] = y[2] ^ lrot(z[1] + y[0],9);
	z[3] = y[3] ^ lrot(z[2] + z[1],13);
	z[0] = y[0] ^ lrot(z[3] + z[2],18);

	return z;
}

template<typename T>
static vector<T> get_vector_part(const vector<T>& v, const vector<int>& number){
	vector<T> r(number.size());
	for(int i = 0; i < number.size(); i++){
		if(number[i] >= v.size()){
			throw invalid_argument("Selected element of the part of vector is out of bound");
		}
		r[i] = v[number[i]];
	}
	
	return r;
}

template<typename T>
static void set_vector_part(vector<T>& toChange, const vector<T>& newValues, const vector<int>& indices){
	if(newValues.size() != indices.size()){
		throw invalid_argument("Values to set need to have an indices in the vector to be changed");
	}
	for(int i = 0; i < newValues.size(); i++){
		if(indices[i] > toChange.size()){
			throw invalid_argument("Indice to replace is out of bound");
		}
		toChange[indices[i]] = newValues[i];
	}
}

vector<uint32_t> Salsa20::rowround(const vector<uint32_t>& y) {
	if(y.size() != 16){
		throw invalid_argument("Argument vector should be of size 16");
	}
	vector<uint32_t> tmp, z(16);
	
	tmp = Salsa20::quaterround(get_vector_part(y, vector<int>{0,1,2,3}));
	set_vector_part(z, tmp, vector<int>{0,1,2,3});
	
	tmp = Salsa20::quaterround(get_vector_part(y, vector<int>{5,6,7,4}));
	set_vector_part(z, tmp, vector<int>{5,6,7,4});
	
	tmp = Salsa20::quaterround(get_vector_part(y, vector<int>{10,11,8,9}));
	set_vector_part(z, tmp, vector<int>{10,11,8,9});
	
	tmp = Salsa20::quaterround(get_vector_part(y, vector<int>{15,12,13,14}));
	set_vector_part(z, tmp, vector<int>{15,12,13,14});
	
	return z;	
}

vector<uint32_t> Salsa20::columnround(const vector<uint32_t>& y){
	if(y.size() != 16){
		throw invalid_argument("Argument vector should be of size 16");
	}
	vector<uint32_t> tmp, z(16);
	
	tmp = Salsa20::quaterround(get_vector_part(y, vector<int>{0,4,8,12}));
	set_vector_part(z, tmp, vector<int>{0,4,8,12});
	
	tmp = Salsa20::quaterround(get_vector_part(y, vector<int>{5,9,13,1}));
	set_vector_part(z, tmp, vector<int>{5,9,13,1});
	
	tmp = Salsa20::quaterround(get_vector_part(y, vector<int>{10,14,2,6}));
	set_vector_part(z, tmp, vector<int>{10,14,2,6});
	
	tmp = Salsa20::quaterround(get_vector_part(y, vector<int>{15,3,7,11}));
	set_vector_part(z, tmp, vector<int>{15,3,7,11});
	
	return z;	
}

vector<uint32_t> Salsa20::doubleround(const vector<uint32_t>& x){
	if(x.size() != 16){
		throw invalid_argument("Argument vector should be of size 16");
	}
	return rowround(columnround(x));
}

uint32_t Salsa20::littleendian(const vector<unsigned char>& b){
	if(b.size() != 4){
		throw invalid_argument("Argument vector should be of size 4");
	}
	uint32_t r = b[0] + (1 << 8) * b[1] + (1 << 16) * b[2] + (1 << 24) * b[3];
	return r;
}

vector<unsigned char> Salsa20::littleendian_inv(uint32_t x){
	vector<unsigned char> r(4);
	for(int i = 0; i < 4; i++){
		r[i] = x % 256;
		x = x >> 8;
	}
	return r;
}

vector<unsigned char> Salsa20::Salsa20(const vector<unsigned char>& x){
	if(x.size() != 64){
		throw invalid_argument("Argument vector should be of size 64");
	}
	vector<unsigned char> t(64);
	vector<uint32_t> y, z;
	
	for(int i = 0; i < 16; i++){
		vector<unsigned char> tmp_x = get_vector_part(x, vector<int>{4*i, 4*i+1, 4*i+2, 4*i+3});
		y.push_back( littleendian(tmp_x) );
	}
	
	z = doubleround(y);
	for(int i =0; i < 9; i++){
		z = doubleround(z);
	}
	
	for(int i = 0; i < 16; i++){
		set_vector_part(t, littleendian_inv(z[i] + y[i]), vector<int>{4*i, 4*i+1, 4*i+2, 4*i+3});
	}
	return t;
}

vector<unsigned char> Salsa20::Salsa20Exp(const vector<unsigned char>& k, const vector<unsigned char>& v){
	bool keyIs32 = k.size() == 32;
	if(k.size() != 16 && !keyIs32){
		throw invalid_argument("Key should be of size 16 or 32");
	}
	if(v.size() != 16){
		throw invalid_argument("V should be a vector of size 16");
	}
	
	int k1begin = keyIs32 ? 16 : 0,
		k1end = keyIs32 ? 32 : 16;
	
	vector<unsigned char> s0{101,120,112,97},
		s1{110,100,32, (keyIs32 ? static_cast<unsigned char>(51) : static_cast<unsigned char>(49)) },
		s2{keyIs32 ? static_cast<unsigned char>(50) : static_cast<unsigned char>(54), 45, 98, 121},
		s3{116, 101, 32, 107},
		x0 = vector<unsigned char>(k.begin(), k.begin() + 16),
		x1 = vector<unsigned char>(k.begin() + k1begin, k.begin() + k1end);
		
	vector<unsigned char> m = s0 + x0 + s1 + v + s2 + x1 + s3;
	return Salsa20(m);
}

vector<unsigned char> Salsa20::Salsa20Encrypt(const vector<unsigned char>& k, const vector<unsigned char>& n, const vector<unsigned char>& m){
	if(k.size() != 16 && k.size() != 32){
		throw invalid_argument("Key should be of size 16 or 32");
	}
	if(n.size() != 8) {
		throw invalid_argument("N should be of size 8");
	}
	vector<unsigned char> c(m.size()), z;
	
	int overflow = 0;
	for(unsigned int i = 0; i < (m.size() >> 6) + 1; i++){
		z = z + Salsa20::Salsa20Exp(k,n + littleendian_inv(i) + littleendian_inv(overflow));
		if( i  == 1 << 32 - 1){
			overflow ++;
		}
	} 
	for(int i = 0; i < m.size(); i++ ){
		c[i] = m[i] ^ z[i];
	}
	return c;
}

