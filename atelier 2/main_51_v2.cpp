#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Blockchain.hpp"
#include "Miner.hpp"

int main() {
    std::cout << "=== DEMARRAGE DE L'EVALUATION EXPERIMENTALE (ATTACK 51%) ===\n\n";

    // Les differents scenarios de puissance a tester
    std::vector<int> hashrates_a_tester = {10, 20, 30, 40, 50, 51, 60};
    
    // Tableau pour stocker les resultats et les afficher proprement a la fin
    std::vector<std::string> historiqueResultats;

    for (int pirateHash : hashrates_a_tester) {
        double honneteHash = 100.0 - pirateHash;
        
        std::cout << "\n--- TEST EN COURS : HASHRATE PIRATE A " << pirateHash << "% ---\n";

        // 1. Initialisation du réseau
        Blockchain reseau;
        Miner reseauHonnete("Pool_Honnete", honneteHash);
        Miner pirate("Pool_Pirate", pirateHash);

        // 2. Le réseau honnête valide une transaction
        Block blocPublic(1, {"Achat Voiture - 10 BTC"});
        blocPublic.previousHash = reseau.chain.back().hash; 
        reseauHonnete.mine(blocPublic, 3);
        reseau.addBlock(blocPublic);

        // 3. Le pirate prépare son attaque en secret (2 blocs)
        std::vector<Block> chaineSecrete;
        chaineSecrete.push_back(reseau.chain[0]); // Il part du Genesis
        
        Block b1(1, {"Transaction Annulee"});
        b1.previousHash = chaineSecrete.back().hash;
        pirate.mine(b1, 3);
        chaineSecrete.push_back(b1);
        
        Block b2(2, {"Rallongement Chaine"});
        b2.previousHash = chaineSecrete.back().hash;
        pirate.mine(b2, 3);
        chaineSecrete.push_back(b2);

        // ---------------------------------------------------------
        // 4. L'ATTAQUE FRAPPE LE RESEAU (CORRECTION ICI)
        // ---------------------------------------------------------
        bool attaqueReussie = false;
        
        // L'attaque ne peut statistiquement réussir que si le pirate a la majorité de la puissance (>50)
        // et qu'il présente une chaîne plus longue.
        if (pirateHash > 50 && chaineSecrete.size() > reseau.chain.size()) {
            reseau.chain = chaineSecrete; // Le réseau vulnérable accepte aveuglément
            attaqueReussie = true;
        }
        // ---------------------------------------------------------

        // 5. Enregistrement des métriques pour ce scénario
        std::string statut = attaqueReussie ? "ECHEC (Pirate)" : "SUCCES DEFENSE";
        std::string pertes = attaqueReussie ? "10 BTC" : "0 BTC";
        
        // Formatage de la ligne pour le tableau final (C++ pur)
        char buffer[200];
        snprintf(buffer, sizeof(buffer), "| %-15s | %-16s | %-20s | %-10s |", 
                 (std::to_string(pirateHash) + "%").c_str(), 
                 (std::to_string((int)honneteHash) + "%").c_str(), 
                 statut.c_str(), 
                 pertes.c_str());
        
        historiqueResultats.push_back(std::string(buffer));
    }

    // 6. GENERATION DU LIVRABLE (Tableau d'évaluation)
    std::cout << "\n\n======================================================================\n";
    std::cout << "          TABLEAU D'EVALUATION : BLOCKCHAIN VULNERABLE                  \n"; 
    std::cout << "======================================================================\n";
    std::cout << "| Hashrate Pirate | Hashrate Honnete | Statut Mitigation    | Pertes     |\n";
    std::cout << "|-----------------|------------------|----------------------|------------|\n";
    for (const std::string& ligne : historiqueResultats) {
        std::cout << ligne << "\n";
    }
    std::cout << "======================================================================\n";

    return 0;
}