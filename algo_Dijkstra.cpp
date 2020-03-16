#include "algo_Dijkstra.h"

algo_Dijkstra::algo_Dijkstra(int const &nb, bool a)
{
	nb_sommets = &nb;
	admin = a;
	need_sommets();
	need_poids();

	/*
		Le constructeur n'appelle pas de lui-même la méthode Dijkstra (publique de ce fait) qui execute l'algorithme.
		J'ai fais ce choix pour permettre d'implementer une autre méthode que need_poids que je trouve très pénible pour les graphes d'ordre important
	*/

}

void algo_Dijkstra::need_sommets() {
	std::cout << "\n Veuillez indiquer les sommets : (Ecrire 'fin' pour arreter)";
	std::string s;
	for (int i(1); i <= *nb_sommets; i++) {
		std::cin >> s;
		if (s == "fin") {
			break;
		}
		else {
			if (s.length() == 1) {
				const char sc = s[0];
				liste_sommets.push_back(sc);
				if (admin)
					std::cout << "Done !";
			}
			else {
				std::cout << "Erreur, le sommet doit etre nomme par une seule lettre. Ressayez.";
				i = i - 1;
			}
		}
		if (i+1 <= *nb_sommets)
			std::cout << "\n Sommet suivant ?";
	}

	if (admin) {
		std::cout << "\n Verification, les sommets sont ";
		for (int i(0); i <= (liste_sommets.size() - 1); ++i)
		{
			std::cout << liste_sommets[i] << " ";
		}
	}

	std::cout << "\n Sommet de depart ?";
	std::cin >> s_dep;
	std::cout << "\n Sommet d'arrivee ?";
	std::cin >> s_ar;
}

void algo_Dijkstra::need_poids() {

	std::cout << "\n Le graphe est il simple ? (o/n)";
	char rep;
	std::cin >> rep;
	if (rep == 'o' || rep == 'O' || rep == '0')
		g_simple = true;

	//Le graphe est-il orienté
	bool g_o = false;
	std::cout << "\n Le graphe est il oriente ? (o/n)";
	rep = ' ';
	std::cin >> rep;
	if (rep == 'o' || rep == 'O' || rep == '0')
		g_o = true;

	std::cout << "\n Determination des poids des chaines de longueur 1 entre les sommets du graphe :";
	std::cout << "\n (Ecrire 'i' s'il n'existe aucune chaine de longueur 1 entre les deux sommets)";
	for (int i(0); i <= (*nb_sommets-1); i++) {
		std::vector <std::string> p_ligne;
		std::string p;
		for (int n(0); n <= (*nb_sommets - 1); n++) {
			if (g_simple && liste_sommets[i] == liste_sommets[n]) {
				p_ligne.push_back("0");
			}
			else {
				if (i >= n && i != 0 && g_o == false) {
					p_ligne.push_back(poids[n][i]);
					std::cout << "\n Poids de la chaine entre " << liste_sommets[i] << " et " << liste_sommets[n] << " = " << poids[n][i];
				}
				else {
					std::cout << "\n Poids de la chaine entre " << liste_sommets[i] << " et " << liste_sommets[n] << " :";
					// La encore, en toute rigueur, il faudrait vérifier que l'utilisateur entre bien un nombre ou "i"
					std::cin >> p;
					p_ligne.push_back(p);
				}
				
			}
		}
		poids.push_back(p_ligne);
	}
	/*
	Instructions de contrôle	
	for (int i(0); i <= (*nb_sommets - 1); i++) {
		for (int n(0); n <= (*nb_sommets - 1); n++) {
			std::cout << "\n Poids de la chaine entre " << liste_sommets[i] << " et " << liste_sommets[n] << " : " << poids[i][n];
		}
	}*/

}

void algo_Dijkstra::Dijkstra() {
	//Initialisation
	//On créé le traditionnel tableau de Dijkstra, un tableau à trois dimensions
	std::vector<std::vector <std::vector <std::string>>> tableau;
	//Attention : la colonne "sommets selectionnés" est dans un autre vector : s_traites
	//On créé aussi la liste des sommets déjà traités
	std::vector<char> s_traites;
	//Et le total des poids 
	int poids_min_total(0);

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
						element.push_back(std::string(1,liste_sommets[q]));
						
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
		for (int s(0); s <= (ligne.size()-1); s++) {
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
	std::cout << "\n\n";
	std::cout << "\nLe tableau de Dijkstra est : ";
	//Affichage du tableau final :
	// 1ere ligne :
	std::cout << "\n";
	for (int i(0); i <= (liste_sommets.size() - 1); i++) {
		std::cout << "   " << liste_sommets[i] << "   |";
	}
	std::cout << " Sommet selectionne";
	//Lignes suivantes
	for (int i(0); i <= (tableau.size() - 1); i++) {
		std::cout << "\n";
		for (int n(0); n <= (tableau[i].size() - 1); n++) {
			if (tableau[i][n][0] == "d")
				std::cout << "   /   | ";
			else
				std::cout << " " << tableau[i][n][0] << "(" << tableau[i][n][1].c_str() << ") | ";
		}
		std::cout << s_traites[i];
	}
	

	// Determination de la chaine la plus courte
	std::vector <std::string> chaine_finale;
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

	std::cout << "\n La chaine la plus courte entre " << s_dep << " et " << s_ar << " est : ";

	//Affichage de la chaine
	for (int i(0); i <= (chaine_finale.size() - 1); i++) {
		if (i != (chaine_finale.size() - 1))
			std::cout << chaine_finale[chaine_finale.size() - i - 1] << " - ";
		else 
			std::cout << chaine_finale[chaine_finale.size() - i - 1];
	}
	std::cout << " (Avec un poids de " << poids_min_total << ") \n";
	system("PAUSE");
}

