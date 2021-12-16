#include "action.h"

Action control(){
	Action action;
	MLV_Keyboard_button key;
	MLV_wait_keyboard(&key, NULL, NULL);

	action.direction = key_to_cardinal(key);

	return action;
	
}

Cardinal key_to_cardinal(MLV_Keyboard_button key){
	switch(key){
		case  MLV_KEYBOARD_DOWN: return SOUTH;
		case  MLV_KEYBOARD_UP: return NORTH;
		case  MLV_KEYBOARD_LEFT: return WEST;
		case  MLV_KEYBOARD_RIGHT: return EAST;
		default : return NEUTRAL;

	}
}
void deplacer_joueur(Floor* etage, Action action){
	Cardinal direction = action.direction;
	switch(direction){
		case NORTH : etage->joueur.pos.y -= 1;break;
		case SOUTH : etage->joueur.pos.y += 1; break;
		case EAST : etage->joueur.pos.x += 1; break;
		case WEST : etage->joueur.pos.x -= 1; break;
		case NEUTRAL: break;
	}
	if (direction != NEUTRAL)
		etage->joueur.direction = direction;
	return;
}
