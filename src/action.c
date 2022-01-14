#include "action.h"
#include "coffre.h"


Action control(){
	Action action;
	MLV_Keyboard_button key;
	action.direction = NEUTRAL;	
	action.choice = -1;
	MLV_wait_keyboard(&key, NULL, NULL);
	key_to_action(key, &action);
	return action;
	
}

int treat_action(Floor*etage){
	Action action = control();
	Monstre* monstre;
	Personnage* pj = &etage->joueur;
	Position next_pos = next_position(etage, action);
	Celltype next_type = position_type(etage, next_pos);
	switch(action.typeaction){ 
		case MOVE : 
			if(is_traversable(next_type))
				deplacer_joueur(etage, action, next_pos);
			else{
				switch(next_type){

					case TREASURE:
					etage->map[next_pos.y][next_pos.x].type = TREASUREO;
					etage->nb_coffre-=1; 
					treasure_opening(pj, init_coffre(etage->number));
					update_cell(etage, next_pos);
					refresh_vision(etage);
					break;

					case MONSTER:
						monstre = &(etage->map[next_pos.y][next_pos.x].entity.monstre);
						switch(hit_enemy(pj, monstre)){
							case -1: return 0;
							case 1: 
								etage->map[next_pos.y][next_pos.x].type = ROOM;
								update_cell(etage, next_pos);
								if(gain_xp(pj, etage->xp_gain))
									choose_stats_lvlup(pj);
						}
						draw_bar_on_ennemy(etage, next_pos, *monstre);
						break;

					case STAIR_DOWN:
						start_etage(etage);
						return 0;
					default:
						break;
					}

			}
			return 1;

		case USE :
			if(pj->selected_item != -1)
				return use_item(pj, pj->selected_item);
			return 0;

		case DISCARD:
			if(pj->selected_item != -1){
				discard_item(pj, pj->selected_item);
				hud(*pj);
				/* Permet juste d'enlever le visuel de l'objet discard */
				display_selected_item(pj->gear[0], -1);
			}
			return 0;

		case MENU :
			return -1;

		case ITEM :
			if(action.choice != -1 && action.choice < pj->len_inventory){
				select_item(pj, action.choice);
				display_selected_item(pj->inventory[action.choice], action.choice);
			}
			return 0;

		default : return 0;
	}

	return 0;

}

int use_item(Personnage* pj, int i){
	Objet* item = &(pj->inventory[i]);
	Objet* gear;
	Objet temp;
	switch(item->type){
		case WEAPON:
		case WAND:
			gear = &(pj->gear[0]);
			temp = *item;
			*item = *gear;
			*gear = temp;
			display_selected_item(*item,i);
			return 1;
		case ARMOR:
			gear = &(pj->gear[1]);
			temp = *item;
			*item = *gear;
			*gear = temp;
			display_selected_item(*item,i);
			return 1;
		case POTION:
			drink_potion(pj, item->specificite.potion, i);
			
			display_selected_item(*item,-1);
			hud(*pj);
			return 0;

	}
	return 0;
}

void key_to_action(MLV_Keyboard_button key, Action* action){
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
		case MLV_KEYBOARD_x:
			action->typeaction = DISCARD;
			break;
		default:
			if(key >= MLV_KEYBOARD_0 && key <=  MLV_KEYBOARD_9){
				action->typeaction = ITEM;
				action->choice = ((key - MLV_KEYBOARD_0))-1;
				/* 1 doit etre le premier et 0 le dernier */
				if(action->choice == -1)
					action->choice = 9;
				break;
			}
			action->typeaction = IDLE;

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


void treasure_opening(Personnage* pj, Coffre chest){
	Action action; 
	Cardinal direction;
	int i;
	int selec = -1;
	draw_chest(chest.contenu, chest.nb_objet);
	action = control();
	while(action.typeaction != MENU){
		direction = action.direction;
		switch(action.typeaction){
			case MOVE:
				switch(direction){
					case WEST:	
						if(selec > 0 && selec < chest.nb_objet)
							selec -= 1;
						else
							selec = 0;
						break;
					case EAST:	
						if(selec > -1 && selec < chest.nb_objet - 1)
							selec += 1;
						else
							selec = chest.nb_objet - 1;
						break;
					default:
						break;
				}
				select_item(pj, -1);
				break;
			
			case ITEM:
				if(action.choice != -1 && action.choice < pj->len_inventory){
					select_item(pj, action.choice);
					selec = pj->selected_item + chest.nb_objet;
				}
				break;
			
			case USE:
				if(selec > -1 && selec < chest.nb_objet) {
					get_new_item(pj, chest.contenu[selec]);
					for(i = selec + 1; i < chest.nb_objet; i++)
						chest.contenu[i - 1] = chest.contenu[i];
					chest.nb_objet--;
				}
				else if(selec >= chest.nb_objet && selec < pj->len_inventory + chest.nb_objet)
					use_item(pj, selec - chest.nb_objet);
				break;
			
			case DISCARD:
				if(pj->selected_item > -1)
					discard_item(pj, pj->selected_item);
				break;
			default:
				break;
		}
		
		if(selec > -1 && selec < chest.nb_objet)
			display_selected_item(chest.contenu[selec], selec - chest.nb_objet - 1);
		else if(selec >= chest.nb_objet && selec < pj->len_inventory + chest.nb_objet)
			display_selected_item(pj->inventory[pj->selected_item], pj->selected_item);
		
		draw_chest(chest.contenu, chest.nb_objet);
		hud(*pj);
		action = control();
	}
	display_selected_item(pj->inventory[pj->selected_item], -1);
}

void choose_stats_lvlup(Personnage* pj){
	Action action;
	Cardinal direction;
	int index = 0;
	int total = 0;
	int stat[3] ={0};
	display_stat(*pj, stat, index);
	action =  control();
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
					if (total > 0 && stat[index] > 0){
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
				
				default:
				break;
			}
		}
		display_stat(*pj, stat, index);
		action = control();
	}
	level_up(pj, stat);
	

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

void start_etage(Floor* etage){
		generate_floor(etage);
		init_vision(etage);

}

int continue_menu(Floor* etage){
	Action action;
	int index = 0;
	Cardinal direction;
	display_continue(index);
	while ((action = control()).typeaction != USE){
		direction = action.direction;
		switch(action.typeaction){
			case MOVE:
				if (direction == NORTH)
					index = 0;
				else if (direction == SOUTH)
					index = 1;
			default:
				break;
		}
		refresh_vision(etage);			
		display_continue(index);
	}
	refresh_vision(etage);			
	return index;

}