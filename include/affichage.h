#ifndef AFFICHAGE
#define AFFICHAGE

#include "cell.h"
#include "floor.h"
/* FONCTION DEBUG, renvoie un char indiquant le type de cell
*/
char cell_into_char(Celltype cell_type);

/* FONCTION DEBUG, affiche le niveau en ascii
*/
void affiche_floor_ascii(Floor* etage);
#endif