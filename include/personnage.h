#ifndef PERSONNAGE
#define PERSONNAGE

#include "attribut.h"
#include "cell.h"
typedef struct personnage{
	Race race;
	Attribut stat;
	Position pos;
	int level;
	int xp;
}Personnage;

#endif