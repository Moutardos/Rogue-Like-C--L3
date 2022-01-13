#include "action.h"
#include "coffre.h"


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
	Position player_pos = etage->joueur.pos;
	Monstre* monstre;
	Personnage* pj = &etage->joueur;
	Position next_pos = next_position(etage, action);
	Celltype next_type = position_type(etage, next_pos);
	switch(action.typeaction){ 
		case MOVE : 
			printf("ACTION IS MOVE\n   ");

			if(is_traversable(next_type))
				deplacer_joueur(etage, action, next_pos);
			else{
				if(next_type == TREASURE){
					etage->map[next_pos.y][next_pos.x].type = TREASUREO;
					etage->nb_coffre-=1;
					Coffre chest = init_coffre(etage->number);
					treasure_opening(pj, chest);
					update_cell(etage, next_pos);
				}
				if (next_type == MONSTER){
					monstre = &(etage->map[next_pos.y][next_pos.x].entity.monstre);
					switch(hit_enemy(etage->joueur, monstre)){
						case -1: return 0;
						case 1: 
							etage->map[next_pos.y][next_pos.x].type = ROOM;
							update_cell(etage, next_pos);
					}
					draw_bar_on_ennemy(etage, next_pos, *monstre);
				}
			}
			return 1;
		case USE :
			switch(position_type(etage, player_pos)){
				default: return 0;
			}
		case MENU :
			return -1;
		case ITEM :
			return 0;
		default : return 0;
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
			if(key >= MLV_KEYBOARD_0 && key <=  MLV_KEYBOARD_9){
				action->typeaction = ITEM;
			}
			action->typeaction = IDLE;
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


int treasure_opening(Personnage* pj, Coffre chest){
	draw_chest(chest.contenu, chest.nb_objet);
	hud(*pj);
	Action action = control();
	Cardinal direction;
	while(action.typeaction != MENU){
		direction = action.direction;
		draw_chest(chest.contenu, chest.nb_objet);
		hud(*pj);
		switch(action.typeaction){
			case MOVE:
				break;
			case USE:
				break;
		}

		action = control();
	}
	
}

int* choose_stats_lvlup(Personnage* pj, int* stat){
	Action action = control();
	Cardinal direction;
	int index = 0;
	int total = 0;
		printf("#####\n%d ATK %c\n%d INT %c\n%d DEF %c\n#####\n",stat[0],index==0?'X':' ',stat[1],index==1?'X':' ',stat[2],index==2?'X':' ');

	while(action.typeaction != USE || total !=3){
		direction = action.direction;
		if (action.typeaction == MOVE){
			switch(direction){
				case EAST:
					if(total < 3){
						total++;
						stat[index]++;
					}
					break;
				case WEST:
					if (total > 0){
						total--;
						stat[index]--;
					}
					break;
				case NORTH:
					if (index > 0)
						index--;
					break;
				case SOUTH:
					if (index < 2)
						index++;
					break;
				}
		}
		printf("#####\n%d ATK %c\n%d INT %c\n%d DEF %c\n#####\n",stat[0],index==0?'X':' ',stat[1],index==1?'X':' ',stat[2],index==2?'X':' ');
		action = control();
	}
	return stat;

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

void exit_game(Floor* etage){
	free_graph();
	free_floor(etage);
}
