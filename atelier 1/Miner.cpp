#include "Miner.hpp"
#include <iostream>

Miner::Miner(const std::string& n, double hr) : nom(n), hashRate(hr) {}

void Miner::mine(Block& block, int difficulty) {
    
    std::string target(difficulty, '0');
    block.hash = block.calculateHash();

    // la boucle de minage 
    while(block.hash.substr(0, difficulty) != target) {
        block.nonce++;
        block.hash = block.calculateHash();
    }
    std::cout << "Block mined by " 
            << nom << " with nonce: "
            << block.nonce << " and hash: " 
            << block.hash 
            << std::endl;
}