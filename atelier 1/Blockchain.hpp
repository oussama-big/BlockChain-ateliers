#pragma once
#include <vector>
#include "Block.hpp"

class Blockchain {
    public:
        std::vector<Block> chain;
        int difficulty;

        Blockchain(int diff);
        Block createGenesisBlock() ;
        Block getLatestBlock() const;
        bool addBlock(Block newBlock);
        bool isChainValid() const;
        bool isBlockValid(const Block& newBlock, const Block& previousBlock) const;
        bool remplacerChaine(const Blockchain& nouvelleChaine);
};