#include "block.cpp"

#include<iostream>
#include<iomanip>

using std::cout;
using std::endl;

int main() {
    Block blk;

    blk.header.version = 1;
    blk.header.timestamp = 1231006505;
    blk.header.target = 0x1d00ffff;
    blk.header.nonce = 2083236893;

    byte arr[CryptoPP::SHA256::DIGESTSIZE] = {0x4a, 0x5e, 0x1e, 0x4b, 0xaa,
    0xb8, 0x9f, 0x3a, 0x32, 0x51, 0x8a, 0x88, 0xc3, 0x1b, 0xc8, 0x7f, 0x61, 0x8f,
    0x76, 0x67, 0x3e, 0x2c, 0xc7, 0x7a, 0xb2, 0x12, 0x7b, 0x7a, 0xfd, 0xed, 0xa3, 0x3b};

    for(int i = 0; i < CryptoPP::SHA256::DIGESTSIZE; i++) {
        blk.header.merkleRootHash[CryptoPP::SHA256::DIGESTSIZE - 1 - i] = arr[i];
        blk.header.prevBlockHash[i] = 0;
    }

    byte* header = reinterpret_cast<byte *>(&blk.header);

    cout << "The bitcoin genesis block is:" << endl;

    for(int i = 0; i < BLOCK_LENGTH; i++) {
        cout << std::hex << std::setw(2) << std::setfill('0') << (int) header[i];
    }

    cout << endl << endl;

    byte digest[CryptoPP::SHA256::DIGESTSIZE];
    blk.getBlockHash(digest);

    cout << "The bitcoin genesis hash(big endian) is:" << endl;

    for(int i = 0; i < CryptoPP::SHA256::DIGESTSIZE; i++) {
        cout << std::hex << std::setw(2) << std::setfill('0') << (int) digest[CryptoPP::SHA256::DIGESTSIZE - 1 - i];
    }
    return 0;
}