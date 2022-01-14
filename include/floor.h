#ifndef GENERATION
#define GENERATION

#include "cell.h"
#include "personnage.h"

#define FLOORW 43
#define FLOORH 63

typedef struct floor{
	Cell map[FLOORH][FLOORW];
	int nb_coffre;
	Personnage joueur;
	int nb_monstre;
	Position* monstres_pos;
	int number;
	int xp_gain;

}Floor;

/* Initalise la map en la remplissant de mur
*/
Floor* init_floor(Personnage pj);

void free_floor(Floor* etage);

/* Genere un etage avec des salles vides respectant les consignes 
*/
int generate_floor(Floor* etage);

/* Genere les elements de l'etage supplementaire (Tresors et monstres)*/
void generate_elem(Floor* etage);

/* Fait apparaitre le personnage principal dans une case a cote de l'escalier
*/
void spawn_perso(Floor * etage);

/* Fait apparaitre un element du type indique dans la position */
void spawn_elem(Floor* etage, Celltype type, Position pos);

/* Verifie si le joueur est a cote de monstre, si oui, rend le monstre aggresif*/
void enemy_turn(Floor* etage);
/* Fonction generation de floor : renvoie 1 si la case mur en position celpos est admissible
*/
int is_eligible(Floor* etage, Position cellpos);

/* Renvoie 1 si les coordonees sont dans les dimensions de l'etage
*/
int is_legal(int x, int y);

/* Renvoie 1 si la case est legal, admissible et n'est pas deja dans toexpand
*/
int is_valid(Floor* etage, Position cellpos, Position* toexpand, int len_expand);


/* supprime la position a l'index precise */
void remove_pos(Position* lst_pos, int index, int* len);

/* Renvoie un tableau de position d'un certain type dans l'etage actuel, les positions
   sont a une distance  range de l'escalier montant. (couteux)
   Renvoie la longueur du tableau dans len.
*/
Position* list_of_tiles(Floor* etage, int* len, int range, Celltype type);

/* Fait apparaitre les tresors proteges par les monstres, verifiant dans chaque room si il n'y a 
   qu'une seule voisine room dans lequel va etre le gardien
   /!\ detruit la liste en parametre
*/
void spawn_protected_treasure(Floor* etage, int len,Position* pos_libre, int nb_salles  );

/* Prend une element au hasard d'un tableau de position, le fait apparaitre et le supprime
   de la liste */
Position spawn_elem_in_list(Floor* etage, Celltype type, int* len, Position* pos_libre);

/* Renvoie la premiere cellule voisine a pos qui est du type indique.*/
Position voisine_type(Floor* etage, Position pos, Celltype type);


/* Renvoie le nombre de case voisine a cellpos dans le terrain et les stockent dans voisines*/
int cell_voisine(Position* voisines, Position cellpos);
/* Retourne le type de cell dans la position pos de l'etage
*/
Celltype position_type(Floor* etage, Position pos);

Cell cell_at_pos(Floor* etage, Position pos);

#endif