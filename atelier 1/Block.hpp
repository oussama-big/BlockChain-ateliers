#pragma once 
#include <string>
#include <ctime>
#include <vector>

class Block {
    public:
        int index;
        long nonce;
        time_t timestamp;
        std::string hash;
        std::string previousHash;
        std::vector<std::string> transactions;
        std::string merkleRoot;

        
        Block(int idx , const std::vector<std::string>& txs);
        std::string calculateHash() const;
        std::vector<std::string> buildMerkleLevel(std::vector<std::string> hashes) const;
        std::string calculateMerkleRoot() const;

};