#ifndef ACTION
#define ACTION

#include "floor.h"
#include "affichage.h"
#include "cell.h"

/* Move vers un ennemie -> Combat */
typedef enum typeaction{
	MOVE, USE, ITEM, MENU, IDLE
}Typeaction;


typedef struct action{
	Cardinal direction;
	Typeaction typeaction;
}Action; 

Action control();

/* Selon le contexte et l'action faite par le joueur, produit un evenement
   Retour : 1 -> le tour du joueur est passe
   			0 -> c'est toujours le tour du joueur
   			-1 -> exit game
*/
int treat_action(Floor*etage);
  
/* Modifie action pour ajouter les informations de la touche utilise par le joueur */
void key_to_action(MLV_Keyboard_button key, Action* action);
/* Renvoie le cardinal selon la touche pressee par le joueur */
Cardinal key_to_cardinal(MLV_Keyboard_button key);

/* Renvoie la position du joueur si il se deplace de un selon sa direction */
Position next_position(Floor* etage, Action action);
/* Deplace la position du personnage jouable dans l'etage selon la direction */
void deplacer_joueur(Floor* etage, Action action, Position new_pos);

/* Libere les donnes alloue avant de quitter le jeu */ 
void exit_game(Floor* etage);

#endif
