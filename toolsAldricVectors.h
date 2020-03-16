#pragma once
#include <vector>
#include <sstream>

/*
	Mini-Librairie pour simplifier l'usage de l'object vector
	@author Aldric L. 2020
*/

namespace alvect {
	//Pour plus de "lisibilit�", je surcharge les m�thodes pour les rendre utilisables qqsoit le type de variables
	bool vectContains(std::vector<std::string> local_vec, std::string e_recherche);
	bool vectContains(std::vector<char> local_vec, char e_recherche);

	int indexElementVect(std::vector <char> local_vect, char e_recherche);
	int indexElementVect(std::vector <std::string> local_vect, std::string e_recherche);
}