#ifndef CELL
#define CELL

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