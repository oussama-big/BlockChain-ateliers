#include <iostream>
#include <vector>
#include <string>
#include "Blockchain.hpp"
#include "Miner.hpp"

int main() {
    // 1. Initialisation des acteurs
    Blockchain reseauHonnete(3);
    Miner reseau("Pool Honnete", 49.0);
    Miner pirate("Pool Pirate", 51.0);

    // 2. Le pirate achète une voiture au marchand sur le réseau public
    std::cout << "[PHASE 1 : LA TRANSACTION LEGITIME]\n";
    Block blocPublic(1, {"Pirate envoie 10 BTC au Marchand (Achat Voiture)"});
    blocPublic.previousHash = reseauHonnete.getLatestBlock().hash;
    
    std::cout << "Le reseau honnete mine le paiement...\n";
    reseau.mine(blocPublic, reseauHonnete.difficulty);
    reseauHonnete.addBlock(blocPublic);
    
    std::cout << "-> Le Marchand voit le paiement valide, il livre la voiture.\n\n";

    // 3. Le pirate crée sa chaîne parallèle secrète en partant du Genesis
    std::cout << "[PHASE 2 : LE MINAGE SECRET DU PIRATE]\n";
    std::vector<Block> chaineSecrete;
    chaineSecrete.push_back(reseauHonnete.chain[0]); // Copie du Genesis public

    // Le pirate remplace le paiement du marchand par un virement vers lui-même
    Block blocSecret1(1, {"Pirate envoie 10 BTC a son propre portefeuille (Double Depense)"});
    blocSecret1.previousHash = chaineSecrete[0].hash;
    
    std::cout << "Le pirate mine secretement son bloc de vol...\n";
    pirate.mine(blocSecret1, reseauHonnete.difficulty);
    chaineSecrete.push_back(blocSecret1);

    // 4. L'avantage des 51% (Le pirate mine plus vite et génère un 2ème bloc d'avance)
    Block blocSecret2(2, {"Transaction quelconque pour allonger la chaine pirate"});
    blocSecret2.previousHash = chaineSecrete[1].hash;
    
    std::cout << "Grace a son hashrate, le pirate mine un 2eme bloc...\n";
    pirate.mine(blocSecret2, reseauHonnete.difficulty);
    chaineSecrete.push_back(blocSecret2);

    // 5. L'écrasement de la base de données (Chain Reorg)
    std::cout << "\n[PHASE 3 : LA DIFFUSION ET LA REORGANISATION]\n";
    std::cout << "Taille de la chaine honnete : " << reseauHonnete.chain.size() << " blocs.\n";
    std::cout << "Taille de la chaine pirate  : " << chaineSecrete.size() << " blocs.\n";

    std::cout << "\nLe pirate diffuse sa chaine au reseau...\n";
    if (reseauHonnete.remplacerChaine(chaineSecrete)) {
        std::cout << "-> ALERTE : Le reseau a adopte la chaine du pirate (Regle de la chaine la plus longue) !\n";
        std::cout << "-> RESULTAT : Le paiement du marchand a disparu de l'historique.\n";
        std::cout << "-> Le pirate possede la voiture ET a recupere ses 10 BTC.\n";
    }

    return 0;
}