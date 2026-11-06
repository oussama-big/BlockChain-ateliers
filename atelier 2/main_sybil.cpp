#include <iostream>
#include <vector>
#include <string>

class NoeudP2P {

public:
    std::string identifiant;
    std::string adresseIP;
    bool estMalveillant;
    NoeudP2P(std::string id, std::string ip, bool malveillant) : identifiant(id), adresseIP(ip), estMalveillant(malveillant) {}
};

int main() {
    std::vector<NoeudP2P> reseau;
    
    // 1. Insertion du noeud cible (Honnete)
    reseau.push_back(NoeudP2P("Victime_Alice", "192.168.1.100", false));
    
    // 2. L'attaquant inonde le P2P avec des clones (Sybil Attack)
    for (int i = 0; i < 99; ++i) {
        reseau.push_back(NoeudP2P("Sybil_Clone_" + std::to_string(i), "10.0.0.55",true));
    }
    
    // 3. Le noeud d'Alice fait un vote pour valider une transaction
    std::cout << "--- DETECTION ET MITIGATION SYBIL ATTACK ---\n";
    int votesHonnetes = 0;
    int votesPirates = 0;
    std::string ipDejaVote = "";
    
    for (const auto& noeud : reseau) {
        if (noeud.adresseIP == "10.0.0.55") {
            if (ipDejaVote == "10.0.0.55") {
                continue; // MITIGATION : On bloque silencieusement le clone
            } else {
                ipDejaVote = "10.0.0.55"; // On accepte juste le tout premier
                votesPirates++;
            }
        } else {
            votesHonnetes++;
        }
    }
    
    std::cout << "\n[MITIGATION ACTIVE] Filtrage par adresse IP en cours...\n";
    std::cout << "-> 98 faux noeuds ont ete bloques (IP dupliquee : 10.0.0.55).\n";
    std::cout << "Votes finaux legitimes : " << votesHonnetes << "\n";
    std::cout << "Votes finaux manipules : " << votesPirates << "\n";
    std::cout << "-> Alice est sauvee, la transaction est rejetee a egalite (1 contre 1).\n";
    return 0;
}