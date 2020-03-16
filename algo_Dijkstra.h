#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

//On appelle mes méthodes pour traiter les vectors pour gagner BEAUCOUP de temps
#include "toolsAldricVectors.h"

class algo_Dijkstra
{
	private:
	std::vector<char> liste_sommets;
	//L'utilisation du type String est discutable, quoique très pratique, compte tenu du risque de poids infini. Il eût peut être été plus efficient de travailler autrement. 
	std::vector<std::vector<std::string>> poids;
	int const *nb_sommets;
	char s_dep, s_ar;
	bool g_simple = false;
	bool admin = false;
	//Ces méthodes réalisent une sorte de matrice (vector poids) dans laquelle elles consignent le poids de la chaine de longueur 1 entre chaque sommet.
	void need_sommets();
	void need_poids();

	public:
	algo_Dijkstra(int const &nb, bool a);
	void Dijkstra();

};

