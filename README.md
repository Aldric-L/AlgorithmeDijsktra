# Algorithme de Dijkstra : La plus court chemin dans un graphe pondéré 
Réalisation de l'algorithme de Dijkstra en C++.
Ce programme peut bien sûr être amélioré : il suppose par exemple qu'il n'existe pas de sommets isolés et utilise trop l'objet std::vector et std::string.

## Usage
Depuis la version 0.2, le code a été modifié pour être plus réutilisable. Ainsi, l'algorithme en lui-même est uniquement la classe algo_Dijkstra. La classe AlgoApp est une classe fille qui sert d'exemple afin de montrer comment récupérer les données auprès de l'utilisateur pour ensuite les transmettre à la classe parente.
Toutes les méthodes de la classe algo_Dijkstra doivent être utilisées dans une structure try catch puisque celles-ci lèvent des exceptions.
Le code peut donc désormais aisément être réutilisé (dans ce cas ne garder que les fichiers algo_Dijkstra.h et .cpp et toolsAldricVectors.h et .cpp), pour, par exemple, être intégré dans une application graphique. 

### Licence
By Aldric L. 2020. Projet scolaire sous licence MIT.