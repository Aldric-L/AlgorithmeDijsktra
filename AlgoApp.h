#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

//On inclut la classe mère pour pouvoir faire l'héritage
#include "algo_Dijkstra.h"

/*
	Cette class est un exemple de classe fille de algo_Dijkstra, afin de montrer comment implementer cette dernière dans un projet plus complet
*/

class AlgoApp : public algo_Dijkstra
{
	private:
	//Ces méthodes réalisent une sorte de matrice (vector poids) dans laquelle elles consignent le poids de la chaine de longueur 1 entre chaque sommet.
	void need_sommets();
	void need_poids();


	public:
	AlgoApp(int const& nb, bool& a);
	// Cette methode affiche le tableau de Dijkstra précedemment généré
	void getTab();
	// Cette methode affiche la chaîne trouvée et son poids
	void getChain();

};

