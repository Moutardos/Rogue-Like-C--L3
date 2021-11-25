#ifndef AFFICHAGE
#define AFFICHAGE

#include "cell.h"
#include "floor.h"

#define WINDOWS_W 1280
#define WINDOWS_H 924
	
/* Initialise la fenetre
*/
void init_graphisme();
/* FONCTION DEBUG, renvoie un char indiquant le type de cell
*/
char cell_into_char(Celltype cell_type);

/* FONCTION DEBUG, affiche le niveau en ascii
*/
void affiche_floor_ascii(Floor* etage);
#endif