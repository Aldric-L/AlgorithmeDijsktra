#include "toolsAldricVectors.h"

bool alvect::vectContains(std::vector<std::string> local_vec, std::string e_recherche) {
	for (int i(0); i < local_vec.size(); i++) {
		if (local_vec[i] == e_recherche) {
			return true;
		}
	}
	return false;
}

bool alvect::vectContains(std::vector<char> local_vec, char e_recherche) {
	for (int i(0); i < local_vec.size(); i++) {
		if (local_vec[i] == e_recherche) {
			return true;
		}
	}
	return false;
}

int alvect::indexElementVect(std::vector <char> local_vect, char e_recherche) {
	std::vector<char>::iterator it = std::find(local_vect.begin(), local_vect.end(), e_recherche);
	return std::distance(local_vect.begin(), it);
}
int alvect::indexElementVect(std::vector <std::string> local_vect, std::string e_recherche) {
	std::vector<std::string>::iterator it = std::find(local_vect.begin(), local_vect.end(), e_recherche);
	return std::distance(local_vect.begin(), it);
}
