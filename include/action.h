#ifndef ACTION
#define ACTION

#include "floor.h"
#include "affichage.h"
#include "cell.h"

/* Move vers un ennemie -> Combat */
typedef enum typeaction{
	MOVE, USE, ITEM, MENU, IDLE, DISCARD
}Typeaction;


typedef struct action{
	Cardinal direction;
	Typeaction typeaction;
	int choice;
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

/* Permet au joueur de naviger dans la selection de loot du tresor */
void treasure_opening(Personnage* pj, Coffre chest);

/* Libere les donnes alloue avant de quitter le jeu */ 
void exit_game(Floor* etage);

/* Genere et affiche un nouveau terrain */
void start_etage(Floor* etage);
/* Permet au joueur de choisir visuelement quelles stats augmenter */
void choose_stats_lvlup(Personnage* pj);

/* Utilise l'item dans la position i de l'inventaire du joueur */
int use_item(Personnage* pj, int i);
/* Permet au joueur de choisir si il veut continuer ou non la partie */
int continue_menu(Floor* etage);
#endif
