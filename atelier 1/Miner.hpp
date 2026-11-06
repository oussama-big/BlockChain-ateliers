#pragma once
#include <string>
#include "Block.hpp"

class Miner {
    public:
        std::string nom;
        double hashRate;
        Miner(const std::string& n, double hr);
        void mine(Block& block, int difficulty);
};