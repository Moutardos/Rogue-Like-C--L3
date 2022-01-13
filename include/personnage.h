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
	int len_potions;
	int selected_item;
}Personnage;

Personnage creation_perso(Race race);


/* Renvoie la limite max d'hp selon les stats */
int get_max_hp(Personnage pj);

/* Renvoie la limite max de mp selon les stats */
int get_max_mp(Personnage pj);



/* Nombre d'xp a atteindre avant d'atteindre le level indique */
int xp_to_levelup(int level);


/* Augmente les 3 stats ([0] = atk, [1] = int, [2] = def) selon ce qu'a choisis le joueur */
void level_up(Personnage* pj, int* stat_lvlup);

/* Le joueur frappe l'ennemie.
   -1 -> pas assez de mp pour la wand
   1 -> kill
   0 -> monstre encore vivant */
int hit_enemy(Personnage pj,Monstre* monstre);

/* Selectione uniquement l'item a la place nb dans l'inventaier*/
void select_item(Personnage* pj, int nb);
/* Renvoie 1 si la potion en parametre est active */
int is_potion_active(Personnage pj, TypePotion type);

/* Ajoute un nouvel item au joueur dans son inventaire si il a de la place */
void get_new_item(Personnage* pj, Objet objet);

/* Supprime de l'inventaire l'objet a la position index */
void discard_item(Personnage* pj, int index);
#endif
