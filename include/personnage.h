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


/* Nombre d'xp a atteindre avant d'atteindre le level indique */
int xp_to_levelup(int level);
#endif