#ifndef PERSONNAGE
#define PERSONNAGE

#include <stddef.h>

#include "attribut.h"
#include "cell.h"
typedef struct personnage{
	Race race;
	Attribut stat;
	Position pos;
	Cardinal direction;
	int level;
	int xp;
	Objet inventory[10];
	Objet gear[2];
	int len_inventory;
	Potion active_potions[NB_POTIONS_ACTIVE];
}Personnage;

Personnage creation_perso(Race race);


/* Nombre d'xp a atteindre avant d'atteindre le level indique */
int xp_to_levelup(int level);


/* Augmente les 3 stats ([0] = atk, [1] = int, [2] = def) selon ce qu'a choisis le joueur */
void level_up(Personnage* pj, int* stat_lvlup);

/* Le joueur frappe l'ennemie.
   -1 -> pas assez de mp pour la wand
   1 -> kill
   0 -> monstre encore vivant */
int hit_enemy(Personnage pj,Monstre* monstre);
#endif
