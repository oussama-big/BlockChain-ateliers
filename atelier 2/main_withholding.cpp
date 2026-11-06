#include <iostream>
#include "Block.hpp"
#include "Miner.hpp"

int main() {
    std::cout << "--- SIMULATION BLOCK WITHHOLDING ET MITIGATION ---\n\n";

    Miner pirate("Pool_Pirate_Bob", 50.0);
    Block currentBlock(1, {"Donnees de test pour la Pool"});
    
    // 1. L'attaque
    std::cout << "[PHASE 1 : L'ATTAQUE DE LA POOL]\n";
    // On lance la fonction mine avec 'true' pour activer le sabotage
    pirate.mine(currentBlock, 3, true); 
    
    // On simule que le pirate a fait tourner son script très longtemps 
    // et encaissé beaucoup de micropaiements de la part de la pool
    pirate.sharesSoumis = 1500; 
    pirate.vraisBlocsTrouves = 0;

    // 2. La détection et mitigation
    std::cout << "\n[PHASE 2 : LA MITIGATION (Systeme central de la Pool)]\n";
    std::cout << "Analyse des statistiques de " << pirate.nom << "...\n";
    std::cout << "Shares soumis (payes) : " << pirate.sharesSoumis << "\n";
    std::cout << "Vrais blocs trouves   : " << pirate.vraisBlocsTrouves << "\n";

    // La Règle métier de cybersécurité :
    if (pirate.sharesSoumis > 1000 && pirate.vraisBlocsTrouves == 0) {
        std::cout << "\n[ALERTE] Probabilite mathematique de malveillance detectee !\n";
        std::cout << "-> Action : Bannissement definitif.\n";
        pirate.estBanni = true;
    }

    // 3. Vérification du blocage
    std::cout << "\n[PHASE 3 : VERIFICATION DU BANNISSEMENT]\n";
    std::cout << "Le pirate tente de se reconnecter pour miner a nouveau...\n";
    
    // Cette exécution sera bloquée par la première ligne de votre nouvelle méthode mine()
    pirate.mine(currentBlock, 3, true); 

    return 0;
}