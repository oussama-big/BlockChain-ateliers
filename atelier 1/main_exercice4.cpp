#include <iostream>
#include <vector>
#include <string>
#include "Blockchain.hpp"
#include "Miner.hpp"

int main() {
    std::cout << "========== EXERCICE 4  ==========\n" << std::endl;

    Blockchain blockchain(3);
    Miner mineur("Mineur Test", 100.0);

    std::cout << "[RESEAU] Minage du Bloc 1 en cours..." << std::endl;
    Block bloc1(1, {"Alice envoie 10 BTC a Bob"});
    bloc1.previousHash = blockchain.getLatestBlock().hash;
    mineur.mine(bloc1, blockchain.difficulty);
    blockchain.addBlock(bloc1);

    std::cout << "[RESEAU] Minage du Bloc 2 en cours..." << std::endl;
    Block bloc2(2, {"Bob envoie 2 BTC a Charlie"});
    bloc2.previousHash = blockchain.getLatestBlock().hash;
    mineur.mine(bloc2, blockchain.difficulty);
    blockchain.addBlock(bloc2);

    std::cout << "\nVerification initiale : La chaine est-elle valide ? -> " 
              << (blockchain.isChainValid() ? "OUI" : "NON") << "\n\n";


    std::cout << "========== ATTAQUE : MODIFICATION DES DONNEES ==========\n";
    std::cout << "Un pirate modifie la transaction du Bloc 1 dans la base de donnees...\n";

    blockchain.chain[1].transactions[0] = "Alice envoie 1000 BTC a Eve"; // Modification malicieuse
    // blockchain.chain[1].merkleRoot = blockchain.chain[1].calculateMerkleRoot(); // Recalcul du Merkle Root
    // blockchain.chain[1].hash = blockchain.chain[1].calculateHash(); // Recalcul du hash du bloc 1

    std::cout << "\nVerification apres modification : La chaine est-elle valide ? -> " 
              << (blockchain.isChainValid() ? "OUI" : "NON") << "\n\n";

    // Explication de l'échec
    std::cout << "--- DIAGNOSTIC DE SECURITE ---\n";
    std::cout << "Nouveau Hash du Bloc 1 : " << blockchain.chain[1].hash << "\n";
    std::cout << "Hash precedent attendu par le Bloc 2 : " << blockchain.chain[2].previousHash << "\n";
    std::cout << "-> Les empreintes ne correspondent plus. Le chainage est brise !\n";

    return 0;
}