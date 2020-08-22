#include "algo_Dijkstra.h"

algo_Dijkstra::algo_Dijkstra(int const &nb, bool a)
{
	s_ar = ' ';
	s_dep = ' ';
	nb_sommets = &nb;
	admin = a;
}

//Setters
void algo_Dijkstra::setPoids(std::vector<std::vector<std::string>>& poids) {
	if (poids.size() != *algo_Dijkstra::nb_sommets) {
		throw std::exception("Error, weights do not match");
	}
	for (unsigned int i(0); i < poids.size(); i++) {
		if (poids[i].size() != *algo_Dijkstra::nb_sommets) {
			throw std::exception("Error, weights do not match");
		}
	}
	algo_Dijkstra::poids = poids;
}
void algo_Dijkstra::setSommets(std::vector<char>& liste_soms) {
	if (liste_soms.size() != *algo_Dijkstra::nb_sommets)
		throw std::exception("Error, inputs do not match with previous datas");

	algo_Dijkstra::liste_sommets = liste_soms;
}
void algo_Dijkstra::setFromStart(char s_dep, char s_ar){
	if (!alvect::vectContains(algo_Dijkstra::liste_sommets, s_dep) || !alvect::vectContains(algo_Dijkstra::liste_sommets, s_ar))
		throw std::exception("Error, start and end do not match with previous datas");

	algo_Dijkstra::s_dep = s_dep;
	algo_Dijkstra::s_ar = s_ar;
}
void algo_Dijkstra::setGrapheType(bool& oriente, bool& simple){
	g_o = oriente;
	g_simple = simple;
}

//Getters
const std::vector<char>& algo_Dijkstra::getSommets() {
	return liste_sommets;
}

const std::vector<std::vector<std::string>>& algo_Dijkstra::getPoids() {
	return poids;
}

const int* const algo_Dijkstra::getNbSoms() {
	return nb_sommets;
}

const std::vector<char> algo_Dijkstra::getDijkstraTabSelected() {
	if (tableau.size() == 0 || tableau.empty()) {
		algo_Dijkstra::Dijkstra();
	}
	return s_traites;
}

const std::vector<std::string> algo_Dijkstra::getDijkstraFinalChain()
{
	if (tableau.size() == 0 || tableau.empty()) {
		algo_Dijkstra::Dijkstra();
	}
	return chaine_finale;
}

const int algo_Dijkstra::getDijkstraFinalChainWeigth()
{
	return poids_min_total;
}

const std::vector<std::vector<std::vector<std::string>>> algo_Dijkstra::getDijkstraTab() {
	if (tableau.size() == 0 || tableau.empty()) {
		algo_Dijkstra::Dijkstra();
	}
	return tableau;
}

const bool algo_Dijkstra::isOriente() {
	return g_o;
}

const bool algo_Dijkstra::isSimple() {
	return g_simple;
}

const bool algo_Dijkstra::isAdmin() {
	return admin;
}


/*
	Méthode privée qui consiste en la réalisation de l'algorithme de Dijkstra
	Ses résultats doivent être récupérés par les getters

	@access private
	@author Aldric L.
*/
void algo_Dijkstra::Dijkstra() {
	if (!algo_Dijkstra::isInitialized())
		throw std::exception("All datas must be set before calling these methods");

	//Initialisation
	//--Premier tour--
	std::vector <std::vector <std::string>> ligne;
	std::vector <std::string> element;
	// Contient trois valeur : poids, sommet de départ, nom du sommet en cours de traitement
	if (admin)
		std::cout << "Première ligne : \n";
	for (int n(0); n < *nb_sommets; n++) {
		if (n == alvect::indexElementVect(liste_sommets, s_dep)) {
			if (admin)
				std::cout << "Traitement de " << liste_sommets[n] << " sommet de départ \n";
			element.clear();
			element.push_back("0");
			element.push_back(std::string(1, s_dep));
			element.push_back(std::string(1, s_dep));
			ligne.push_back(element);
		}
		else {
			if (admin)
				std::cout << "Traitement de " << liste_sommets[n] << " sommet auxiliaire \n";
			element.clear();
			element.push_back("i");
			element.push_back(std::string(1, s_dep));
			element.push_back(std::string(1, liste_sommets[n]));
			ligne.push_back(element);
		}
	}
	//On ajoute la ligne au tableau
	tableau.push_back(ligne);
	//On ajoute le sommet de départ à la colonne des sommets déjà traités
	s_traites.push_back(s_dep);
	ligne.clear();

	// -- L'algorithme en lui-même -- 
	//Tant que le dernier sommet traité n'est pas le sommet de départ, on poursuit l'analyse
	//l'entier n correspond au numéro de ligne du vector tableau qui est en cours de traitement
	if (s_traites.empty())
		throw std::exception("Unknown error during the Dijkstra algorithm");

	for (int n(1); s_ar != s_traites.back(); n++) {
		if (admin)
			std::cout << "\n \n Ligne " << n << "\n";
		ligne.clear();
		for (int q(0); q <= (*nb_sommets - 1); q++) {
			element.clear();
			//Si le sommet a déjà été traité, on l'indique
			if (alvect::vectContains(s_traites, liste_sommets[q])) {
				if (admin)
					std::cout << "Traitement de " << liste_sommets[q] << " deja traite \n";
				element.push_back("d");
				element.push_back("d");
				element.push_back(std::string(1, liste_sommets[q]));
			}
			else {
				//On cherche ici le poids de la chaine entre le dernier sommet traité et le sommet q
				if (poids[alvect::indexElementVect(liste_sommets, s_traites.back())][q] != "i") {
					//Le poids n'est pas infini, on peut donc caster le poids en int et y ajouter le poids total précedent
					int element_poids = stoi(poids[alvect::indexElementVect(liste_sommets, s_traites.back())][q]) + poids_min_total;
					//On cherche si à la ligne précedente, un poids meilleur n'avait pas été trouvé
					if (tableau[n - 1][q][0] != "i" && stoi(tableau[n - 1][q][0]) < element_poids) {
						//L'ancien poids était donc meilleur, on copie donc l'ancienne case, tableau nommé element constitué du nom du sommet et de son poids
						//Ancien poids
						element.push_back(tableau[n - 1][q][0]);
						//Ancienne origine
						element.push_back(tableau[n - 1][q][1]);
						//Sommet traité 
						element.push_back(std::string(1, liste_sommets[q]));

						if (admin)
							std::cout << "Traitement de " << liste_sommets[q] << " ancien poids meilleur \n";
					}
					else {
						//Le poids est bien meilleur ou équivalent, on enregistre donc la trouvaille
						if (admin)
							std::cout << "Traitement de " << liste_sommets[q] << " poids enregistre \n";
						element.push_back(std::to_string(element_poids));
						element.push_back(std::string(1, s_traites.back()));
						//Sommet traité 
						element.push_back(std::string(1, liste_sommets[q]));
					}
				}
				else {
					//Le poids est infini, on cherche donc si à la ligne précedente, un poids meilleur n'avait pas été trouvé
					if (tableau[n - 1][q][0] != "i") {
						//L'ancien poids était donc meilleur, ou égal, on copie donc l'ancienne case, tableau nommé element constitué du nom du sommet et de son poids
						//Ancien poids
						element.push_back(tableau[n - 1][q][0]);
						//Ancienne origine
						element.push_back(tableau[n - 1][q][1]);
						//Sommet traité 
						element.push_back(std::string(1, liste_sommets[q]));

						if (admin)
							std::cout << "Traitement de " << liste_sommets[q] << " ancien poids meilleur \n";
					}
					//L'ancien poids était aussi infini, on le reporte donc l'ancien poids infini.
					else {
						//L'ancien poids était donc meilleur, ou égal, on copie donc l'ancienne case, tableau nommé element constitué du nom du sommet et de son poids
						//Ancien poids
						element.push_back(tableau[n - 1][q][0]);
						//Ancienne origine
						element.push_back(tableau[n - 1][q][1]);
						//Sommet traité 
						element.push_back(std::string(1, liste_sommets[q]));
						if (admin)
							std::cout << "Traitement de " << liste_sommets[q] << " ancien poids infini aussi \n";
					}
				}
			}
			ligne.push_back(element);
		}
		//Sélection du meilleur sommet de la ligne
		if (admin)
			std::cout << "Sélection du meilleur sommet de la ligne " << n << "\n";
		std::vector <std::string> meilleur_e;
		meilleur_e.clear();
		meilleur_e.push_back("i");
		meilleur_e.push_back("i");
		std::string index_meilleur_sommet;
		for (int s(0); s <= (ligne.size() - 1); s++) {
			if (admin) {
				std::cout << "\n Nb d'elements dans la ligne : " << ligne.size();
				std::cout << "\n index : " << s;
				std::cout << "\n Traitement de " << liste_sommets[s];
			}
			//On verifie ici que le meilleur sommet enregistré n'ai pas un poids infini
			if (meilleur_e[0] != "i" && meilleur_e[0] != "d") {
				//Le poids n'est pas infini, on peut donc caster le poids en int
				int element_poids = stoi(meilleur_e[0]);
				//On cherche si à l'élement s n'a pas un meilleur poids
				if (ligne[s][0] != "i" && ligne[s][0] != "d" && stoi(ligne[s][0]) < element_poids) {
					meilleur_e = ligne[s];
					index_meilleur_sommet = meilleur_e[2];
				}
			}
			else {
				//Le meilleur poids est infini, on cherche donc un sommet dont le poids n'est pas lui aussi infini
				if (ligne[s][0] != "i" && ligne[s][0] != "d") {
					//Dans ce cas, ce sommet devient le meilleur
					meilleur_e = ligne[s];
					index_meilleur_sommet = meilleur_e[2];
				}
			}
		}
		//Une fois la sélection terminée, on ajoute donc aux sommets traités le sommet sélectionné et son poids devient le poids total
		poids_min_total = stoi(meilleur_e[0]);
		s_traites.push_back(index_meilleur_sommet[0]);
		if (admin)
			std::cout << "\n Selection de " << index_meilleur_sommet;
		tableau.push_back(ligne);
	}
	

	// Determination de la chaine la plus courte
	std::string last_sommet = std::string(1, s_traites.back());
	chaine_finale.push_back(last_sommet);

	while (last_sommet != std::string(1, s_dep)) {
		int index_last_som = alvect::indexElementVect(liste_sommets, last_sommet[0]);
		for (int i(tableau.size() - 1); i != 0; i--) {
			if (tableau[i][index_last_som][0] != "d") {
				chaine_finale.push_back(tableau[i][index_last_som][1]);
				last_sommet = tableau[i][index_last_som][1];
				if (admin)
					std::cout << "\nAjout d'un sommet : " << tableau[i][index_last_som][1];
				break;
 			}
		}
	}
}

bool algo_Dijkstra::isInitialized(){
	if (liste_sommets.empty())
		return false;
	if (poids.empty())
		return false;
	if (s_ar == ' ')
		return false;
	if (s_dep == ' ')
		return false;
	return true;
}

