#include "test.h"
#include "attribut.h"
#include "affichage.h"
#include "floor.h"
#include "action.h"
int main(int argc, char const *argv[]){
	Action action;
	Personnage pj;
	Floor* etage;
	int showmap = 0;
	int i;
	int action_done;
	int stop = 0;
	srand(time(NULL));

	if (!test())
		return 1;

	if (!init_mlv())
		return 1;
	

	for(i = 1; i < argc; i++)
		if (strcmp("-m", argv[i]) == 0)
			showmap = 1;
	
	while(!stop){
		pj = creation_perso(HUMAN);
 		etage = init_floor(pj);
		start_etage(etage);
		while ( !stop && etage->joueur.stat.Hp > 0){
			action_done = treat_action(etage);
			if (action_done == -1)
				stop = continue_menu(etage);
			if (action_done == 0)
				continue;
			if(showmap)
				affiche_floor_ascii(etage);
			enemy_turn(etage); 
			potion_effects(&etage->joueur);
			hud(etage->joueur);
		}
		if (etage->joueur.stat.Hp <= 0)
			stop = continue_menu(etage);
	}
	
	exit_game(etage);
	return 0;
}
