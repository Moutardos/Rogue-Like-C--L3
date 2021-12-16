#ifndef ACTION
#define ACTION

#include "floor.h"
#include "affichage.h"
#include "cell.h"

typedef struct action{
	Cardinal direction
	/* union {
		inserer les autres actions
	}*/
}Action;

Action control();

Cardinal key_to_cardinal(MLV_Keyboard_button key);

/* Deplace la position du personnage jouable dans l'etage selon la direction */
void deplacer_joueur(Floor* etage, Action action);


#endif
