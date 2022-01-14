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
}Objet;



/* Renvoie une arme avec une qualite aleatoire */
Objet generate_weapon(int etage);
void print_weapon(Objet weapon);

/* Renvoie une armure avec une qualité aléatoire */
Objet generate_armor(int etage);
void print_armor(Objet armor);

/* Renvoie un objet généré aléatoirement */
Objet generate_objet(int etage, TypeObjet type);
#endif
