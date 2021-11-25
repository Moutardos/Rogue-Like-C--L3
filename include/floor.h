#ifndef GENERATION
#define GENERATION

#include "cell.h"
#include "personnage.h"

#define FLOORW 43
#define FLOORH 63

typedef struct floor{
	Cell map[FLOORH][FLOORW];
	/* treasor count
	*/
	Personnage joueur;
}Floor;

/* Initalise la map en la remplissant de mur
*/
Floor* init_floor();

/* Genere un etage avec des salles vides respectant les consignes 
*/
int generate_floor(Floor* etage);

/* Fait apparaitre le personnage principal dans une case a cote de l'escalier
*/
void spawn_perso(Floor * etage);
/* Fonction generation de floor : renvoie 1 si la case mur en position celpos est admissible
*/
int is_eligible(Floor* etage, Position cellpos);

/* Renvoie 1 si les coordonees sont dans les dimmensions de l'etage
*/
int is_legal(int x, int y);

/* Renvoie 1 si la case est legal, admissible et n'est pas deja dans toexpand
*/
int is_valid(Floor* etage, Position cellpos, Position* toexpand, int len_expand);

void remove_pos(Position* toexpand, int index, int* len_expand);

/* Retourne le type de cell dans la position pos de l'etage
*/
Celltype position_type(Floor* etage, Position pos);
#endif