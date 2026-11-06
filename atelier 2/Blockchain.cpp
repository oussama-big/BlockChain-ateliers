#include "Blockchain.hpp"
#include <iostream>

Blockchain::Blockchain(int diff) {
    difficulty = diff;
    chain.push_back(createGenesisBlock());
}

Blockchain::Blockchain() {
    difficulty = 3; // Valeur par défaut si non spécifiée
    chain.push_back(createGenesisBlock());
}
Block Blockchain::createGenesisBlock() {
    std::vector<std::string> genesisTxs = {"Genesis Block"};
    Block genesis(0, genesisTxs);
    genesis.previousHash = std::string(64,'0');
    genesis.hash = genesis.calculateHash();
    return genesis;

}

Block Blockchain::getLatestBlock() const {
    return chain.back();
}

bool Blockchain::addBlock(Block newBlock) {

    if (newBlock.previousHash != getLatestBlock().hash) {
        std::cerr << "Error: Previous hash does not match the latest block's hash." << std::endl;
        return false;
    }

    if (newBlock.hash != newBlock.calculateHash()) {
        std::cerr << "Error: Block hash is invalid." << std::endl;
        return false;
    }
    chain.push_back(newBlock);
    return true;
}

bool Blockchain::isChainValid() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i - 1];

        if (currentBlock.merkleRoot != currentBlock.calculateMerkleRoot()) {
            return false;
        }

        if (currentBlock.hash != currentBlock.calculateHash()) {
            return false;
        }

        if (currentBlock.previousHash != previousBlock.hash) {
            return false;
        }
    }
    return true;
}

bool Blockchain::remplacerChaine(const std::vector<Block>& newChain) {
    // Règle d'or du consensus : la chaîne valide la plus longue gagne
    if (newChain.size() > this->chain.size()) {
        int orphansGenerated = chain.size() - 1;
        std::cout << "\n[MODULE DE DETECTION] Analyse de la reorganisation..." << std::endl;

        if (orphansGenerated > MAX_REORG_DEPTH) {
            std::cout << "[MITIGATION ACTIVE] Rejet de la chaine malveillante !" << std::endl;
            std::cout << "-> Raison : La reorganisation est trop profonde (" 
                      << orphansGenerated << " blocs orphelins potentiels)." << std::endl;
            std::cout << "-> Le paiement du marchand est protege et reste dans l'historique.\n";
            
            // On retourne false : la chaîne du pirate est rejetée, l'attaque échoue.
            return false; 
        }

        if (orphansGenerated == 1){
            std::cout << "[INFO] 1 bloc orphelin. Probable latence reseau naturelle (Fork benin)." << std::endl;
        }

        totalOrphanBlocks += orphansGenerated;
        this->chain = newChain;
        return true;
    }
    return false;
}