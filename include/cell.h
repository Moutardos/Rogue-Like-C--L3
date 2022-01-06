#ifndef CELL
#define CELL

#include "coffre.h"
typedef enum  {
	WALL, ROOM, MONSTER, TREASURE,
	TREASUREO, STAIR_UP, STAIR_DOWN
} Celltype;

typedef union entity {
		/*Monster monster;*/
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


#endif