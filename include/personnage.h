#ifndef PERSONNAGE
#define PERSONNAGE

#include "attribut.h"
#include "cell.h"
typedef struct personnage{
	Race race;
	Attribut stat;
	Position pos;
	Cardinal direction;
	int level;
	int xp;
}Personnage;

Personnage creation_perso(Race race);
#endif