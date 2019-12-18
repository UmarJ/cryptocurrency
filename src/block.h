#ifndef BLOCK_H
#define BLOCK_H

#define BLOCK_LENGTH 80

#include<crypto++/rsa.h>

typedef uint8_t byte; // looks cooler lol

class Block {

    public:

        struct blockHeader { // 80 bit block header
            uint32_t version; // a 4 byte useless value to confirm with bitcoin standard, may be changed later
            byte prevBlockHash[CryptoPP::SHA256::DIGESTSIZE];
            byte merkleRootHash[CryptoPP::SHA256::DIGESTSIZE];
            uint32_t timestamp;
            uint32_t target;
            uint32_t nonce;
        } header;

        Block();
        void getBlockHash(byte*);
        void updateMerkleRootHash(byte*);
};

#endif