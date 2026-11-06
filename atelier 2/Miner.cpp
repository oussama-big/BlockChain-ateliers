#include "Miner.hpp"
#include <iostream>

Miner::Miner(const std::string& n, double hr) : nom(n), hashRate(hr) {}

void Miner::mine(Block& block, int difficulty, bool blockWithholdingAttack) {
    
    if (this->estBanni) {
        std::cout << "[REJETE] Le mineur " << this->nom << " est banni du reseau et ne peut plus miner.\n";
        return; 
    }

    std::string target(difficulty, '0');
    
    // Difficulté simulée de la pool (ex: 1 seul zéro pour un "Share")
    int poolDifficulty = 1; 
    std::string poolTarget(poolDifficulty, '0');
    
    block.hash = block.calculateHash();
    int sharesVoles = 0; // Compteur pour l'argent volé à la pool

    // La boucle de recherche
    while(true) { 
        
        // 1. Est-ce qu'on a trouvé LE vrai bloc du réseau (ex: 3 ou 4 zéros) ?
        if (block.hash.substr(0, difficulty) == target) {
            
            if (blockWithholdingAttack) {
                std::cout << "\n[ALERTE SABOTAGE] Le pirate (" << nom << ") a trouve le VRAI bloc (Nonce: " << block.nonce << ") !\n";
                std::cout << "[ALERTE SABOTAGE] Il jette la solution a la poubelle au lieu de la donner a la pool.\n";
                std::cout << "-> BILAN : Il a ete paye par la pool pour " << sharesVoles << " shares, mais la pool ne gagne rien !\n";
                break; // Le pirate s'arrête ici (ou passe au bloc suivant en réalité)
            } else {
                // Mineur honnête : il a trouvé le bloc, on met à jour son compteur
                this->vraisBlocsTrouves++;
                break; 
            }
        }

        // 2. Si on n'a pas le vrai bloc, est-ce qu'on a un Share pour la pool (ex: 1 zéro) ?
        // (Ceci doit être en dehors du 'if' précédent !)
        if (block.hash.substr(0, poolDifficulty) == poolTarget) {
            this->sharesSoumis++; // Tous les mineurs incrémentent ça (pour que la pool vérifie)
            if (blockWithholdingAttack) {
                sharesVoles++; // Le pirate compte son butin
            }
        }

        // 3. On incrémente le nonce pour tester la combinaison suivante
        // (Ceci doit s'exécuter à CHAQUE itération de la boucle !)
        block.nonce++;
        block.hash = block.calculateHash();
    }

    // 4. Affichage de fin uniquement si ce n'est pas un sabotage silencieux
    if (!blockWithholdingAttack) {
        std::cout << "Block mined by " << nom << " with nonce: " << block.nonce 
                  << " and hash: " << block.hash << std::endl;
    }
}

// Pseudo-code de mitigation à intégrer dans la gestion de votre pool
void Miner::evaluerMineur(Miner& mineur) {
    // Si le mineur a soumis énormément de shares (ex: 1000) mais 0 vrai bloc
    if (mineur.sharesSoumis > 1000 && mineur.vraisBlocsTrouves == 0) {
        std::cout << "[MITIGATION ACTIVE] Anomalie statistique detectee pour le mineur : " << mineur.nom << "\n";
        std::cout << "-> Action : BANNISSEMENT de la pool (Suspicion de Block Withholding).\n";
        mineur.estBanni = true;
    }
}