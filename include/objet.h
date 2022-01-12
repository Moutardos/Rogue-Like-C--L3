#ifndef OBJET
#define OBJET

#include "attribut.h"
#define NB_POTIONS_ACTIVE 3

typedef enum typeObjet{
	ARMOR, POTION, WAND, WEAPON
}TypeObjet;

typedef enum typePotion{
	PSOIN, PMAGIE, PREGEN,
	PPRECISION, PAPPRENTISSAGE
}TypePotion;

typedef struct potion{
	TypePotion type;
	int remaining_turn;

}Potion;

typedef union specificite{
	int qualite;
	Potion potion;
}Specificite;


typedef struct objet{
	TypeObjet type;
	Specificite specificite;
	Attribut bonus;
	int cooldown;
	int active;
}Objet;



/* Renvoie une arme avec une qualite aleatoire */
Objet generate_weapon(int etage);
void print_weapon(Objet weapon);
#endif
