#include "block.h"

Block::Block() {};

void Block::getBlockHash(byte* digest) {
    byte temp[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SHA256().CalculateDigest(temp, reinterpret_cast<byte *>(&header), BLOCK_LENGTH);
    CryptoPP::SHA256().CalculateDigest(digest, temp, CryptoPP::SHA256::DIGESTSIZE);
}
