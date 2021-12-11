#ifndef ACTION
#define ACTION

#include "floor.h"
#include "affichage.h"

Cardinal control();

Cardinal key_to_cardinal(MLV_Keyboard_button key);
void deplacer_joueur(Floor* etage, Cardinal direction);


#endif
