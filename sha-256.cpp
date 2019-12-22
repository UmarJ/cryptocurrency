#include<iostream>
#include <string>
#include <bitset>
using namespace std;

#define SHA2_SHFR(x, n)    (x >> n)
#define SHA2_ROTR(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define SHA2_ROTL(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define SHA2_CH(x, y, z)  ((x & y) ^ (~x & z))
#define SHA2_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHA256_F1(x) (SHA2_ROTR(x,  2) ^ SHA2_ROTR(x, 13) ^ SHA2_ROTR(x, 22))
#define SHA256_F2(x) (SHA2_ROTR(x,  6) ^ SHA2_ROTR(x, 11) ^ SHA2_ROTR(x, 25))
#define SHA256_F3(x) (SHA2_ROTR(x,  7) ^ SHA2_ROTR(x, 18) ^ SHA2_SHFR(x,  3))
#define SHA256_F4(x) (SHA2_ROTR(x, 17) ^ SHA2_ROTR(x, 19) ^ SHA2_SHFR(x, 10))
#define SHA2_UNPACK32(x, str)                 \
{                                             \
    *((str) + 3) = (uint8) ((x)      );       \
    *((str) + 2) = (uint8) ((x) >>  8);       \
    *((str) + 1) = (uint8) ((x) >> 16);       \
    *((str) + 0) = (uint8) ((x) >> 24);       \
}
#define SHA2_PACK32(str, x)                   \
{                                             \
    *(x) =   ((uint32) *((str) + 3)      )    \
           | ((uint32) *((str) + 2) <<  8)    \
           | ((uint32) *((str) + 1) << 16)    \
           | ((uint32) *((str) + 0) << 24);   \
}

const int K[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
int m_H[8] = { 0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19 };

string TextToBinaryString(string words) {
	string binaryString = "";
	for (char& letter : words) {
		binaryString += bitset<8>(letter).to_string();
	}
	return binaryString;
}

string padding(string msg) {
	int l = strlen(msg.c_str()) * 8;
	int k = 448 - (l + 1);
	while (k < 0) {
		k += 512;
	}
	msg = TextToBinaryString(msg);
	string lbin = bitset<64>(l).to_string();
	msg += bitset<1>(1).to_string();
	for(int i =0 ;i < k;i++)
	{
		msg += "0";
	}
	msg += lbin;
	return msg;
}

int **stringtoint(string msg) {
	int length = strlen(msg.c_str());
	int **Mptr = new int*[length/512];
	for (int i = 0; i < length/512; i++) {
		Mptr[i]  = new int[16];
	}
	for (int i = 0; i < (length / 512); i++) {
		for (int j = 0; j < 16; j++) {
			Mptr[i][j] = stoi(msg.substr(32 * j, (32 * (j + 1))).c_str(),0,2);
		}
	}
	return Mptr;
}
int* sha256(int** Mptr,int length) {
	int W[64];
	
	for(int i = 0;i<length/512;i++){
		int T1, T2, a=m_H[0], b=m_H[1], c=m_H[2], d=m_H[3], e=m_H[4], f=m_H[5], g=m_H[6], h=m_H[7];
		for (int j = 0; j < 16; j++) {
			W[j] = Mptr[i][j];
		}
		for (int j = 16; j < 64; j++)
		{
			W[j] = SHA256_F4(W[j - 2]) + W[j - 7] + SHA256_F3(W[j - 15]) + W[j - 16];
		}
		
		for (int j = 0; j < 64; j++) {	
			T1 = h + SHA256_F2(e) + SHA2_CH(e,f,g) + K[j] + W[j];
			T2 = SHA256_F1(a) + SHA2_MAJ(a,b, c);
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;

			if (j == 1) {
				printf("0x%X", T1);
			}
		}
		m_H[0] += a;
		m_H[1] += b;
		m_H[2] += c;
		m_H[3] += d;
		m_H[4] += e;
		m_H[5] += f;
		m_H[6] += g;
		m_H[7] += h;
	}
	return m_H;
}
int main() {
	//cout << (sha256(stringtoint(padding("abc")),1)[0]);
	string a = padding("abc");
	cout << padding("abc") << endl;
	int b = sha256(stringtoint(a),512)[0];
	//printf("0x%X",b);
}



