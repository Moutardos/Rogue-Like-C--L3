#ifndef CELL
#define CELL

#include "coffre.h"
#include "monstre.h"
typedef enum  {
	WALL, ROOM, MONSTER, TREASURE,
	TREASUREO, STAIR_UP, STAIR_DOWN
} Celltype;

typedef union entity {
		Monstre monstre;
		Coffre coffre;
}Entity;
typedef struct cell{
	Celltype type;
	Entity entity;
}Cell;

typedef enum cardinal {
	NORTH, EAST,
	SOUTH, WEST,
	NEUTRAL
}Cardinal;

typedef struct position{
	int x;
	int y;
} Position;



/* Renvoie l'information si la cellule peut etre traverse par le joueur */
int is_traversable(Celltype type);

/* Renvoie 1 si les coordonees sont egaux, sinon 0 */
int pos_is_equals(Position pos1, Position pos2);
#endif