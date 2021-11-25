#ifndef CELL
#define CELL

#define CELLSIZE 32 /* Taille d'une cell en pixel */
typedef enum  {
	WALL, ROOM, MONSTER, TREASURE,
	STAIR_UP, STAIR_DOWN
} Celltype;

typedef struct cell{
	Celltype type;
/*	union {
		Monster monster;
		Treasure treasure;
	}*/
}Cell;



typedef struct position{
	int x;
	int y;
} Position;

#endif