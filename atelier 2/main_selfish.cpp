#include <iostream>
#include <vector>
#include <string>
#include "Blockchain.hpp"
#include "Miner.hpp"

int main() {
    // 1. Initialisation : Le pirate a une minorité de puissance (ex: 30%)
    Blockchain reseauPublic(3); 
    Miner reseauHonnete("Pool Honnete", 70.0);
    Miner pirateEgoiste("Pool Selfish", 30.0);

    std::cout << "--- SIMULATION SELFISH MINING ---\n\n";

    // 2. PHASE DE RETENTION (Le pirate a de la chance et trouve le bloc en premier)
    std::cout << "[PHASE 1 : RETENTION SECRETE]\n";
    std::vector<Block> chaineSecrete;
    chaineSecrete.push_back(reseauPublic.chain[0]); // Copie du Genesis

    Block blocSecret1(1, {"Transaction quelconque 1 (Le pirate encaisse la recompense)"});
    blocSecret1.previousHash = chaineSecrete[0].hash;
    
    std::cout << "Le pirate trouve un bloc mais le garde SECRET...\n";
    pirateEgoiste.mine(blocSecret1, reseauPublic.difficulty);
    chaineSecrete.push_back(blocSecret1);
    std::cout << "-> Avance du pirate : +1 bloc.\n\n";

    // 3. PHASE DE CREATION D'AVANCE (Le pirate mine sur sa propre chaine)
    std::cout << "[PHASE 2 : CREATION DE L'AVANCE]\n";
    Block blocSecret2(2, {"Transaction quelconque 2"});
    blocSecret2.previousHash = chaineSecrete[1].hash;
    
    std::cout << "Le pirate utilise son avance pour trouver un 2eme bloc en secret...\n";
    pirateEgoiste.mine(blocSecret2, reseauPublic.difficulty);
    chaineSecrete.push_back(blocSecret2);
    std::cout << "-> Avance du pirate : +2 blocs.\n\n";

    // 4. REACTION DU RESEAU HONNETE (Ils trouvent enfin le bloc 1)
    std::cout << "[PHASE 3 : LA COURSE A LA PUBLICATION]\n";
    Block blocPublic(1, {"Transaction Honnete"});
    blocPublic.previousHash = reseauPublic.getLatestBlock().hash;
    
    std::cout << "Le reseau honnete trouve enfin un bloc et s'apprete a le diffuser...\n";
    reseauHonnete.mine(blocPublic, reseauPublic.difficulty);
    std::cout << "-> ALERTE POUR LE PIRATE : La concurrence a trouve un bloc !\n\n";

    // 5. LA PUBLICATION CALCULEE (Le coup de grace)
    std::cout << "[PHASE 4 : L'ECRASEMENT]\n";
    std::cout << "Le pirate diffuse immediatement sa chaine secrete de 2 blocs pour couper l'herbe sous le pied du reseau.\n";
    
    if (reseauPublic.remplacerChaine(chaineSecrete)) {
        std::cout << "-> Le reseau public adopte la chaine du pirate (2 blocs > 1 bloc).\n";
        std::cout << "-> RESULTAT : Le bloc des mineurs honnetes devient ORPHELIN.\n";
        std::cout << "-> Le reseau honnete a gaspille 100% de son energie pour rien.\n";
    }

    return 0;
}