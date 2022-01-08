#include "action.h"

Action control(){
	Action action;
	MLV_Keyboard_button key;
	action.direction = NEUTRAL;	
	MLV_wait_keyboard(&key, NULL, NULL);
	key_to_action(key, &action);
	return action;
	
}

int treat_action(Floor*etage){
	Action action = control();
	printf("nb coffre :%d\n", etage->nb_coffre);
	printf("OK WE HERE     ");

	Position next_pos = next_position(etage, action);
	Celltype next_type = position_type(etage, next_pos);
	switch(action.typeaction){ 
		case MOVE : 
			printf("ACTION IS MOVE\n   ");


			if(is_traversable(next_type)){
				deplacer_joueur(etage, action, next_pos);

				return 1;
			}
			else{
				if(next_type == TREASURE){
					etage->map[next_pos.y][next_pos.x].type = TREASUREO;
					printf("aa\n");
					open_coffre(etage->map[next_pos.y][next_pos.y]);
										printf("aa\n"); 
					etage->nb_coffre-=1;
					update_cell(etage, next_pos);
				return 1;
				}
			}
			break;
		case USE :

			break;
		default : ;
			/* todo */
	}
			printf("char at [%d][%d]\n", etage->joueur.pos.y, etage->joueur.pos.x);

	return 0;

}

void key_to_action(MLV_Keyboard_button key, Action* action){
	int nb;
	switch(key){
		case  MLV_KEYBOARD_DOWN:  
		case  MLV_KEYBOARD_UP:    
		case  MLV_KEYBOARD_LEFT:  
		case  MLV_KEYBOARD_RIGHT:
			action->direction = key_to_cardinal(key);
			action->typeaction = MOVE;
			break;
		case MLV_KEYBOARD_ESCAPE:
			action->typeaction = MENU;
			break;
		case MLV_KEYBOARD_SPACE:
		case MLV_KEYBOARD_RETURN:
			action->typeaction = USE;
			break;
		default:
			if(key >= MLV_KEYBOARD_0 && key <=  MLV_KEYBOARD_9)
				action->typeaction = ITEM;

				/* todo ajouter item tudu */

	}
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



Position next_position(Floor* etage, Action action){
	Cardinal direction = action.direction;
	Position next_pos = etage->joueur.pos;
	switch(direction){
		case NORTH : next_pos.y -= 1; break;
		case SOUTH : next_pos.y += 1; break;
		case EAST : next_pos.x += 1; break;
		case WEST : next_pos.x -= 1; break;
		case NEUTRAL: break;
	}
	return next_pos;
}
void deplacer_joueur(Floor* etage, Action action, Position new_pos){
	Cardinal direction = action.direction;
	etage->joueur.pos = new_pos;
	if (direction != NEUTRAL){
		etage->joueur.direction = direction;
		movement_vision(etage, direction);
	}

}

