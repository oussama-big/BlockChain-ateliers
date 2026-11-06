#pragma once
#include <vector>
#include "Block.hpp"

class Blockchain {
    public:
        std::vector<Block> chain;
        int difficulty;
        int totalOrphanBlocks = 0;

        // NOUVEAU : La limite de blocs qu'on accepte de rendre orphelins lors d'un fork
        const int MAX_REORG_DEPTH = 0;

        Blockchain(int diff);
        Blockchain();
        Block createGenesisBlock() ;
        Block getLatestBlock() const;
        bool addBlock(Block newBlock);
        bool isChainValid() const;
        bool isBlockValid(const Block& newBlock, const Block& previousBlock) const;
        bool remplacerChaine(const std::vector<Block>& newChain);
};