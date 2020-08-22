#include "AlgoApp.h"

/*
	Cette class est un exemple de classe fille de algo_Dijkstra, afin de montrer comment implementer cette dernière dans un projet plus complet
*/


AlgoApp::AlgoApp(int const& nb, bool& a) : algo_Dijkstra(nb, a){
	need_sommets();
	need_poids();
}

void AlgoApp::need_sommets() {
	bool admin(algo_Dijkstra::isAdmin());
	std::vector<char> local_liste_sommets;
	std::cout << "\n Veuillez indiquer les sommets : (Ecrire 'fin' pour arreter)";
	std::string s;
	const int *nb_sommets = algo_Dijkstra::getNbSoms();
	for (int i(1); i <= *nb_sommets; i++) {
		std::cin >> s;
		if (s == "fin") {
			break;
		}
		else {
			if (s.length() == 1) {
				while (!std::regex_match(s, std::regex{ "[A-Z]+" }) || s.length() != 1) {
					std::cout << "Merci d'entrer une lettre majuscule valide :";
					std::cin >> s;
				}
				const char sc = s[0];
				local_liste_sommets.push_back(sc);
				if (admin)
					std::cout << "Done !";
			}
			else {
				std::cout << "Erreur, le sommet doit etre nomme par une seule lettre. Ressayez.";
				i = i - 1;
			}
		}
		if (i + 1 <= *nb_sommets)
			std::cout << "\n Sommet suivant ?";
	}

	if (admin) {
		std::cout << "\n Verification, les sommets sont ";
		for (unsigned int i(0); i < local_liste_sommets.size(); ++i)
		{
			std::cout << local_liste_sommets[i] << " ";
		}
	}

	char s_dep, s_ar;
	std::string rep;
	std::cout << "\n Sommet de depart ?";
	std::cin >> rep;
	while (!std::regex_match(rep, std::regex{ "[A-Z]+" }) || rep.length() != 1 || !alvect::vectContains(local_liste_sommets, rep[0])) {
		std::cout << "Merci d'entrer une lettre majuscule valide, et qui figure dans la liste des sommets :";
		std::cin >> rep;
	}
	s_dep = rep[0];
	rep = "";
	std::cout << "\n Sommet d'arrivee ?";
	std::cin >> rep;
	while (!std::regex_match(rep, std::regex{ "[A-Z]+" }) || rep.length() != 1 || !alvect::vectContains(local_liste_sommets, rep[0]) || rep[0] == s_dep) {
		std::cout << "Merci d'entrer une lettre majuscule valide, et qui figure dans la liste des sommets :";
		std::cin >> rep;
	}
	s_ar = rep[0];

	try {
		algo_Dijkstra::setSommets(local_liste_sommets);
		algo_Dijkstra::setFromStart(s_dep, s_ar);
	}
	catch (const std::exception & e) {
		std::cout << "Erreur fatale. Fin du programme : " << e.what() << std::endl;
		return;
	}
}

void AlgoApp::need_poids() {
	const int* nb_sommets = algo_Dijkstra::getNbSoms();

	//On récupère la liste des sommets que l'on a précedement réalisée
	std::vector <char> local_liste_sommets(getSommets());
	std::vector<std::vector<std::string>> local_poids;

	std::cout << "\n Le graphe est il simple ? (o/n)";
	std::string rep;
	std::cin >> rep;
	while (rep != "o" && rep != "n") {
		std::cout << "Merci d'entrer une reponse valide :";
		std::cin >> rep;
	}

	bool g_simple = false;
	if (rep == "o")
		g_simple = true;

	//Le graphe est-il orienté
	bool g_o = false;
	std::cout << "\n Le graphe est il oriente ? (o/n)";
	rep = " ";
	std::cin >> rep;
	while (rep != "o" && rep != "n") {
		std::cout << "Merci d'entrer une reponse valide :";
		std::cin >> rep;
	}
	if (rep == "o")
		g_o = true;

	algo_Dijkstra::setGrapheType(g_o, g_simple);

	std::cout << "\n Determination des poids des chaines de longueur 1 entre les sommets du graphe :";
	std::cout << "\n (Ecrire 'i' s'il n'existe aucune chaine de longueur 1 entre les deux sommets)";
	for (int i(0); i <= (*nb_sommets - 1); i++) {
		std::vector <std::string> p_ligne;
		std::string p;
		for (int n(0); n <= (*nb_sommets - 1); n++) {
			if (g_simple && local_liste_sommets[i] == local_liste_sommets[n]) {
				p_ligne.push_back("0");
			}
			else {
				if (i >= n && i != 0 && g_o == false) {
					p_ligne.push_back(local_poids[n][i]);
					std::cout << "\n Poids de la chaine entre " << local_liste_sommets[i] << " et " << local_liste_sommets[n] << " = " << local_poids[n][i];
				}
				else {
					std::cout << "\n Poids de la chaine entre " << local_liste_sommets[i] << " et " << local_liste_sommets[n] << " :";
					std::cin >> p;
					while (!std::regex_match(p, std::regex{ "[+]?[0-9]+" }) && p != "i") {
						std::cout << "Merci d'entrer un poids valide (entier positif ou 'i') :";
						std::cin >> p;
					}
					p_ligne.push_back(p);
				}

			}
		}
		local_poids.push_back(p_ligne);
	}

	//On passe à la classe mère, la véritable classe, la pondération des sommets du graphe sous la forme d'un vector<vector<string>>
	try {
		algo_Dijkstra::setPoids(local_poids);
	}
	catch (const std::exception & e) {
		std::cout << "Erreur fatale. Fin du programme : " << e.what() << std::endl;
		return;
	}
	/*
	Instructions de contrôle
	for (int i(0); i <= (*nb_sommets - 1); i++) {
		for (int n(0); n <= (*nb_sommets - 1); n++) {
			std::cout << "\n Poids de la chaine entre " << local_liste_sommets[i] << " et " << local_liste_sommets[n] << " : " << local_poids[i][n];
		}
	}*/

}

void AlgoApp::getTab() {
	std::vector <char> local_liste_sommets;
	std::vector<std::vector <std::vector <std::string>>> tableau;
	std::vector<char> s_traites;
	//Ce bloc try catch permet d'attraper toutes les erreurs levées par la méthode Dijkstra sous jacente.
	//Cela permet notamment d'arreter le programme s'il manque une donnée par exemple.
	try {
		local_liste_sommets = getSommets();
		tableau = getDijkstraTab();
		s_traites = getDijkstraTabSelected();
	}
	catch (const std::exception & e){
		std::cout << "Erreur fatale. Fin du programme : " << e.what() <<  std::endl;
		return;
	}
	

	std::cout << "\n\n";
	std::cout << "\nLe tableau de Dijkstra est : ";
	//Affichage du tableau final :
	// 1ere ligne :
	std::cout << "\n";
	for (unsigned int i(0); i < local_liste_sommets.size(); i++) {
		std::cout << "   " << local_liste_sommets[i] << "   |";
	}
	std::cout << " Sommet selectionne";
	//Lignes suivantes
	if (tableau.size() != 0) {
		for (unsigned int i(0); i < tableau.size(); i++) {
			std::cout << "\n";
			for (int n(0); n < tableau[i].size(); n++) {
				if (!tableau[i][n].empty() && tableau[i][n][0] == "d")
					std::cout << "   /   | ";
				else if (!tableau[i][n].empty())
					std::cout << " " << tableau[i][n][0] << "(" << tableau[i][n][1].c_str() << ") | ";
				else
					std::cout << " Err | ";
			}
			std::cout << s_traites[i];
		}
	}
	else {
		std::cout << std::endl << "Erreur, le tableau de Dijkstra est vide" << std::endl;
	}
	
}
void AlgoApp::getChain() {
	std::vector<std::string> chaine_finale;
	unsigned int finalweight;
	try {
		chaine_finale = algo_Dijkstra::getDijkstraFinalChain();
		finalweight = algo_Dijkstra::getDijkstraFinalChainWeigth();
	}
	catch (const std::exception & e) {
		std::cout << "Erreur fatale. Fin du programme :" << e.what() << std::endl;
		return;
	}

	if (chaine_finale.empty()) {
		std::cout << std::endl << "Erreur, la chaine n'a pas ete trouvee." << std::endl;
		return;
	}

	std::cout << "\n La chaine la plus courte entre " << chaine_finale.back() << " et " << chaine_finale.front() << " est : ";

	//Affichage de la chaine
	for (unsigned int i(0); i < chaine_finale.size(); i++) {
		if (i != (chaine_finale.size() - 1))
			std::cout << chaine_finale[chaine_finale.size() - i - 1] << " - ";
		else
			std::cout << chaine_finale[chaine_finale.size() - i - 1];
	}
	std::cout << " (Avec un poids de " << finalweight << ") \n";
}