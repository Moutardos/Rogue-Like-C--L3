#include "test.h"
#include "attribut.h"
#include "affichage.h"
#include "floor.h"
#include "action.h"
int main(int argc, char const *argv[]){
	Action action;
	Personnage pj = creation_perso(HUMAN);
	Floor* etage = init_floor(pj);
	int action_done;
	if (!test())
		return 1;

	if (!init_mlv())
		return 1;
	generate_floor(etage);
	init_vision(etage);

	while ( (action_done = treat_action(etage)) != -1){
		if (action_done == 0)
			continue;
		affiche_floor_ascii(etage);
		enemy_turn(etage); /* todo : enemy return la position du fight si besoin puis le fait */
		hud(etage);

	}
	exit_game(etage);
	return 0;
}
