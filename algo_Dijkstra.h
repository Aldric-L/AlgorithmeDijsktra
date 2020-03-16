#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

//On appelle mes m�thodes pour traiter les vectors pour gagner BEAUCOUP de temps
#include "toolsAldricVectors.h"

class algo_Dijkstra
{
	private:
	std::vector<char> liste_sommets;
	//L'utilisation du type String est discutable, quoique tr�s pratique, compte tenu du risque de poids infini. Il e�t peut �tre �t� plus efficient de travailler autrement. 
	std::vector<std::vector<std::string>> poids;
	int const *nb_sommets;
	char s_dep, s_ar;
	bool g_simple = false;
	bool admin = false;
	//Ces m�thodes r�alisent une sorte de matrice (vector poids) dans laquelle elles consignent le poids de la chaine de longueur 1 entre chaque sommet.
	void need_sommets();
	void need_poids();

	public:
	algo_Dijkstra(int const &nb, bool a);
	void Dijkstra();

};

