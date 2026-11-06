#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include "Block.hpp"

struct Validator {
    std::string name;
    int stake;
};

int main() {
    std::cout << "========== EXERCICE 3 : TEST PROOF OF STAKE ==========\n";
    
    std::vector<Validator> validators = {
        {"Validateur A", 10},
        {"Validateur B", 50},
        {"Validateur C", 40}
    };

    std::vector<std::string> txs = {"Transaction validee par PoS"};
    Block blocTest(1, txs);
    blocTest.previousHash = "0000000000000000000000000000000000000000000000000000000000000000";

    // Début du chronomètre pour le PoS
    auto start = std::chrono::high_resolution_clock::now();

    // 1. Sélection pseudo-aléatoire basée sur le stake
    int totalStake = 100;
    std::mt19937 gen(12345); // Graine fixe pour reproductibilité
    std::uniform_int_distribution<> distrib(1, totalStake);
    int tirage = distrib(gen);

    std::string selectedValidator;
    int somme = 0;
    for (const auto& v : validators) {
        somme += v.stake;
        if (tirage <= somme) {
            selectedValidator = v.name;
            break;
        }
    }

    // 2. Le validateur sélectionné signe le bloc (1 seul calcul de hash, pas de boucle de force brute)
    blocTest.hash = blocTest.calculateHash();

    // Fin du chronomètre
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Le reseau a selectionne : " << selectedValidator << " (Tirage: " << tirage << "/100)\n";
    std::cout << "Hash du bloc : " << blocTest.hash << "\n";
    std::cout << "-> Temps d'execution PoS : " << std::fixed << duration.count() << " secondes.\n";

    return 0;
}