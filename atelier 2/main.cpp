#include <iostream>
#include <vector>
#include <string>
#include <chrono> // Pour calculer le temps d'exécution
#include "Blockchain.hpp"
#include "Miner.hpp"

int main() {
    std::cout << "========== EXERCICE 2 : TEST DES DIFFICULTES POW ==========\n" << std::endl;
    
    Miner mineur("Mineur Test", 100.0);
    std::vector<std::string> txs = {"Transaction de test pour le temps d'execution"};
    
    // On va tester les niveaux de difficulté de 1 à 5
    for (int difficulte = 1; difficulte <= 5; difficulte++) {
        // On recrée un bloc neuf à chaque fois pour que le nonce reparte de 0
        Block blocTest(1, txs);
        blocTest.previousHash = "0000000000000000000000000000000000000000000000000000000000000000";

        std::cout << "Niveau de difficulte : " << difficulte << " (Recherche de " << difficulte << " zeros)" << std::endl;

        // Démarrage du chronomètre
        auto start = std::chrono::high_resolution_clock::now();

        // Le mineur commence son travail
        mineur.mine(blocTest, difficulte);

        // Arrêt du chronomètre
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << "-> Temps d'execution : " << duration.count() << " secondes.\n" << std::endl;
    }

    return 0;
}