#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <exception>

//On appelle mes m�thodes pour traiter les vectors pour gagner BEAUCOUP de temps
#include "toolsAldricVectors.h"

/*
	Cette class est d�sormais une class abstraite, afin de s�parer la partie math�matique de l'affichage et du dialogue avec l'utilisateur
	Cette class peut donc �tre utilis�e en dehors de cet exemple.
*/

class algo_Dijkstra
{
	private:
		int const* nb_sommets;
		char s_dep, s_ar;
		bool g_simple = false;
		bool g_o = false;
		bool admin = false;
		//L'utilisation du type String est discutable, quoique tr�s pratique, compte tenu du risque de poids infini. Il e�t peut �tre �t� plus efficient de travailler autrement. 
		std::vector<std::vector<std::string>> poids;
		std::vector<char> liste_sommets;
		//On cr�� le traditionnel tableau de Dijkstra, un tableau � trois dimensions
		std::vector<std::vector <std::vector <std::string>>> tableau;
		//Attention : la colonne "sommets selectionn�s" est dans un autre vector : s_traites
		//On cr�� aussi la liste des sommets d�j� trait�s
		std::vector<char> s_traites;
		//Et le total des poids 
		int poids_min_total = 0;
		//Le vector contenant la cha�ne finale
		std::vector <std::string> chaine_finale;

		//La m�thode priv�e pour lancer l'algorithme Dijkstra. Ses resultats seront stock�s dans les attributs pr�c�demment d�clar�s.
		void Dijkstra();
		//Cette methode permet � la methode Dijkstra de savoir si elle peut s'executer correctement (si toutes les infos sur le graphe ont bien �t� transmises)
		bool isInitialized();

	// Cette class �tant abstraite, une classe fille doit donc �tre charg�e de l'utiliser
	// Pour cela, elle dispose de getters et setters
	protected:
		algo_Dijkstra(int const& nb, bool a);

		void setPoids(std::vector<std::vector<std::string>>& poids);
		void setSommets(std::vector<char>& liste_soms);
		void setFromStart(char s_dep, char s_ar);
		void setGrapheType(bool& oriente, bool& simple);

		const bool isOriente();
		const bool isSimple();
		const bool isAdmin();
		const int* const getNbSoms();
		const std::vector<char>& getSommets();
		const std::vector<std::vector<std::string>>& getPoids();
		const std::vector<std::vector <std::vector <std::string>>> getDijkstraTab();
		const std::vector<char> getDijkstraTabSelected();
		const std::vector<std::string> getDijkstraFinalChain();
		const int getDijkstraFinalChainWeigth();

};

