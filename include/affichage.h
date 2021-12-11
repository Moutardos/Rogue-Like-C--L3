#ifndef AFFICHAGE
#define AFFICHAGE

#include <MLV/MLV_all.h>

#include "cell.h"
#include "floor.h"

#define WINDOWS_W 1280
#define WINDOWS_H 924
#define CELLSIZE 132/* Taille d'une cell en pixel (normalement 32) */
#define RANGE 7

typedef enum cardinal {
	NORTH, EAST,
	SOUTH, WEST,
	NEUTRAL
}Cardinal;

/* Initialise la fenetre
*/

void init_mlv();

int load_cell(Floor* etage, Position cellpos, MLV_Image** image);


const char* image_url(Celltype cell_type, int theme);


int init_vision(Floor* etage, MLV_Image*** cell_image);

int movement_vision(Floor* etage, MLV_Image*** cell_image, Cardinal direction);

/* FONCTION DEBUG, renvoie un char indiquant le type de cell
*/
char cell_into_char(Celltype cell_type);

/* FONCTION DEBUG, affiche le niveau en ascii
*/
void affiche_floor_ascii(Floor* etage);
#endif