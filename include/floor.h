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
	int number;
}Floor;

/* Initalise la map en la remplissant de mur
*/
Floor* init_floor(Personnage pj);

/* Genere un etage avec des salles vides respectant les consignes 
*/
int generate_floor(Floor* etage);
/* Genere les elements de l'etage (Tresors et monstres)*/
int generate_elem(Floor* etage);
/* Fait apparaitre le personnage principal dans une case a cote de l'escalier
*/
void spawn_perso(Floor * etage);

int spawn_monster(Floor* etage, Position* pos_libre, int* len);
int spawn_treasure(Floor* etage, Position* pos_libre, int* len);

/* Fonction generation de floor : renvoie 1 si la case mur en position celpos est admissible
*/
int is_eligible(Floor* etage, Position cellpos);

/* Renvoie 1 si les coordonees sont dans les dimmensions de l'etage
*/
int is_legal(int x, int y);

/* Renvoie 1 si la case est legal, admissible et n'est pas deja dans toexpand
*/
int is_valid(Floor* etage, Position cellpos, Position* toexpand, int len_expand);


/* supprime la position a l'index precise */
void remove_pos(Position* lst_pos, int index, int* len);

/* Renvoie un tableau de position d'un certain type dans l'etage actuel, les positions
   sont a une distance  range du personnage.
   Renvoie la longueur du tableau dans len.
*/
Position* list_of_tiles(Floor* etage, int* len, int range, Celltype type);

/* Retourne le type de cell dans la position pos de l'etage
*/
Celltype position_type(Floor* etage, Position pos);
#endif