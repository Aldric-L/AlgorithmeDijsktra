#include <iostream>
#include <regex>
#include "AlgoApp.h"

/*
    Programme permettant la réalisation d'un tableau de Dijkstra et la recherche du plus court chemin dans un graphe
    
    @author Aldric L. 2020
    @version 0.2

    "Auto correction" :
    Cet algorithme utilise beaucoup l'object vector, qui est peu optimisé. 
    Il serait plus rigoureux mais très long de le remplacer par des tableaux statiques là où c'est possible.
*/

int main()
{
    std::string nb_sommets; 
    std::cout << " -------------------------------------------------------------";
    std::cout << "\n Programme permettant l'execution de l'algorithme de Dijkstra. \n";
    std::cout << " ------------------------------------------------------------- \n\n";
    std::cout << "INITIALISATION \n";

    while (true) {
        std::cout << "Indiquez le nombre de sommets :";
        std::cin >> nb_sommets;

        //J'inclue un système de controle, si un bug se produisait
        bool admin(false);
        int nb(0);
        //Par simplification, on ne teste pas si la saisie est bien un int... On suppose dans ce type d'algorithme que l'utilisateur est intelligent.
        if (nb_sommets == "admin") {
            admin = true;
            std::cout << "Administrateur reconnu : Indiquez le nombre de sommets :";
            std::cin >> nb_sommets;
        }

        while (!std::regex_match(nb_sommets, std::regex{ "[+]?[0-9]+" })) {
            std::cout << "Merci d'entrer un entier positif valide :";
            std::cin >> nb_sommets;
        }
        nb = std::stoi(nb_sommets);

        int const n(nb);

        if (nb == 0 || nb == 1) {
            std::cout << "\n L'algorithme de Dijkstra ne presente pas d'interet pour les graphes d'ordre 1 ou 0";
            return 0;
        }

        AlgoApp algo(n, admin);
        algo.getTab();
        algo.getChain();

        std::string rep;
        std::cout << std::endl << "Fin de l'algorithme ! Voulez-vous relancer celui-ci pour un autre graphe ? (o/n)";
        std::cin >> rep;
        if (rep != "o" && rep != "O") {
            break;
        }
    }
    

}
