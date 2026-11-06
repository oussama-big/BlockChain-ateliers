#pragma once
#include <string>
#include "Block.hpp"

class Miner {
    public:
        std::string nom;
        double hashRate;
        int sharesSoumis = 0;
        int vraisBlocsTrouves = 0;
        bool estBanni = false;
        Miner(const std::string& n, double hr);
        void mine(Block& block, int difficulty, bool blockWithholdingAttack = false);
        void evaluerMineur(Miner& mineur);
};