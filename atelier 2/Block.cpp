#include "Block.hpp"
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

std::string sha256(const std::string& data){
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(
        reinterpret_cast<const unsigned char*>(data.c_str()),
        data.length(),
        hash
    );
    std::stringstream ss;

    for (int i = 0 ; i < SHA256_DIGEST_LENGTH; i++){
        ss  << std::hex 
            << std::setw(2)
            << std::setfill('0') 
            << (int)hash[i];
    }

    return ss.str();
}

Block::Block(int idx , const std::vector<std::string>& txs ){
    index = idx ;
    transactions = txs ;
    timestamp = std::time(nullptr);
    nonce = 0;
    previousHash = "";
    merkleRoot = calculateMerkleRoot();
}

std::vector<std::string> Block::buildMerkleLevel(std::vector<std::string> hashes) const{
    if (hashes.empty()) return {""}; // Sécurité si le bloc est vide
    if (hashes.size() == 1) return hashes;

    std::vector<std::string> nextLevel;
    if (hashes.size() % 2 != 0) {
        hashes.push_back(hashes.back());
    }
    for (size_t i = 0; i < hashes.size(); i += 2) {
        nextLevel.push_back(sha256(hashes[i] + hashes[i+1]));
    }
    return buildMerkleLevel(nextLevel);
}


std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index 
        << previousHash 
        << timestamp 
        << merkleRoot 
        << nonce;
    return sha256(ss.str());
}

std::string Block::calculateMerkleRoot() const {
    if (transactions.empty()) return "";

    std::vector<std::string> txHashes;
    for (const auto& tx : transactions) {
        txHashes.push_back(sha256(tx));
    }
    return buildMerkleLevel(txHashes)[0];
}