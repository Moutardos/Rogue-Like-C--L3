#include "affichage.h"
#include "attribut.h"
#include <stdio.h>
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

static MLV_Image* image_perso;
static MLV_Image* background;
static MLV_Image* portrait;
static MLV_Image* off_limit;
static MLV_Image*** vision_joueur;
static MLV_Image* bars;
int init_mlv(){
		unsigned int i = 0;
        
        MLV_create_window( "ver 0.23 !", "roguelike", WINDOWS_W, WINDOWS_H );
        image_perso = MLV_load_image("art/sprite/char/mc.png");
        MLV_resize_image(image_perso, CELLSIZE , CELLSIZE );
        
        off_limit = MLV_load_image("art/map/offlimit.png");
        
        background = MLV_load_image("art/hud/bg.png");
        MLV_draw_image(background,0,0);
        
        portrait = MLV_load_image("art/hud/portrait.png");
        MLV_resize_image(off_limit, CELLSIZE , CELLSIZE );
        
        vision_joueur =  malloc(sizeof(MLV_Image**) * (RANGE *2));
        if( vision_joueur == NULL){
        	free(vision_joueur);
        	return 0;
        }
        	
		bars = MLV_create_image(0,0);

        for(i = 0; i < RANGE*2; i++){
			vision_joueur[i] = malloc(sizeof(MLV_Image*) * (RANGE * 2));
			if (vision_joueur[i] == NULL){
				free_vision_joueur(i);
				return 0;
			}
        }

        return 1;

;
}

void free_graph(){
	int i = 0;
	MLV_clear_window(MLV_COLOR_WHITE);
	MLV_free_window();
	if (vision_joueur != NULL){
		free_vision_joueur(RANGE * 2);
	}
}
void free_vision_joueur(int n){
	unsigned int i;
	for (i = 0; i <n; i++){
		free(vision_joueur[i]);
	}
	free(vision_joueur);
}
int load_cell( Floor* etage, Position cellpos, MLV_Image** image){
	Celltype type; 
	TypeMonstre type_monstre;

	if (is_legal(cellpos.x, cellpos.y)){


		type = position_type(etage, cellpos);
		if( type != ROOM && type != WALL){ /* type transparent */
			*image = MLV_load_image(image_url(ROOM,0)); 
			if (type == MONSTER){
				type_monstre = cell_at_pos(etage, cellpos).entity.monstre.type;
				MLV_draw_image_on_image(MLV_load_image(image_url_monstre(type_monstre)), *image, 0,0);
			}
			else
				MLV_draw_image_on_image(MLV_load_image(image_url(type,0)), *image, 0,0);
		}
		else
			*image = MLV_load_image(image_url(type, 0));

		MLV_resize_image(*image, CELLSIZE, CELLSIZE);

	} 
	else{  
		/* on load une image "fantome" derriere les limites de la carte, empechant le joueur de rentrer et permettant
		   au programme de pouvuoir free cette partie de la vision du joueur*/
		*image = MLV_load_image(image_url(WALL,0));
        MLV_resize_image(*image , 1,1 );

	}
	/* else affiche carre noir */
	return 1;
}


const char* image_url(Celltype cell_type, int theme){
	/* theme represente le biome de l'etage TODO*/
	switch(cell_type){
		case WALL: return "art/map/wall01.png";
		case ROOM: return "art/map/floor03.png";
		case STAIR_DOWN: return "art/map/stairdown.png";
		case STAIR_UP: return "art/map/stairup.png";
		case TREASURE: return "art/map/treasure.png";
		case TREASUREO: return "art/map/treasureo.png";
		default : return "art/map/notfound.png";
	} 
}

const char* image_url_monstre(TypeMonstre monstre){
	switch(monstre){
		case ALIEN: return "art/sprite/enemy/Etest.png";

	}
}
int init_vision(Floor* etage){
	/* remplie case +x autour du perso*/ 
	Position pos_joueur = etage->joueur.pos;
	Position cellpos;
	unsigned i;    
	unsigned j; 
 

	for (j = 0; j <RANGE; ++j){ 
		for (i = 0; i <RANGE; ++i){

			cellpos.x = pos_joueur.x - (RANGE/2 + RANGE%2) + i +1; 
			cellpos.y = pos_joueur.y - (RANGE/2 + RANGE%2) + j +1;

			load_cell(etage, cellpos, &vision_joueur[j][i]); 
			MLV_draw_image(vision_joueur[j][i], CELLSIZE * i, CELLSIZE * j);

			if( cellpos.x == pos_joueur.x && cellpos.y == pos_joueur.y){
				MLV_draw_image(image_perso, CELLSIZE * i, CELLSIZE * j);
			} 


		}
	}
	hud(etage);
	MLV_actualise_window();
	return 0; 
}

int movement_vision(Floor* etage, Cardinal direction){
	unsigned int i, j;
	unsigned int start;
	int placement[2] = {0,0}; /* [0] = x [1] = y */
	int movement;
	int last_line;
	int decalage_y, decalage_x;
	Position player_pos = etage->joueur.pos;
	Position next_pos;
	Position cellpos;

	if (NULL == vision_joueur)
		return 1;

	switch(direction){
		case NORTH : placement[1] = 1; movement = -1 ; start = RANGE - 1; break;
		case EAST  : placement[0] = 1; movement = 1; start = 0; break;
		case SOUTH : placement[1] = 1; movement = 1; start = 0;     break;
		case WEST  : placement[0] = 1; movement = -1; start = RANGE -1;     break;
		case NEUTRAL : return 1;
	}


	
	/** SCROLLING **/
	/* Pour chaque mouvement (Horizontale| Vertical devant|avant) la case i,j doit prendre l'image de celle devant elle,
	   sauf la derniere qui sera load a partir des donnes de l'etage */

	decalage_y =  (placement[1] - movement)/2 * placement[1]; /* permet d'ignorer la derniere ligne
									formule : 
									x = 1,  y = 1 -> h = 0     h = (y - x)/2
									x = -1, y = 1 -> h = 1     h = (y - x)/2

									x = 0  y = 1   ->   h = 0  h =  (y - x)/2 * y
									x = 0  y = -1  ->   h = 0  h =  (y - x)/2 * y
								*/
	decalage_x = (placement[0] - movement)/2 * placement[0];
	printf("Decalage y   %d     \n", decalage_y);
	for(j = start  ; j < RANGE - (1 - decalage_y)*placement[1]   && j >= 0 + decalage_y*placement[1]; j += movement){
		for(i = start ; i < RANGE - (1 - decalage_x)*placement[0]  && i >= 0 + decalage_x*placement[0]; i += movement){
			/* Ignore si la prochaine case est vide (en dehors du plateau) */
				printf("1\n");
			/* position de la prochaine case dans la vision du joueur*/
			next_pos.x = i + movement * placement[0];
			next_pos.y = j + movement * placement[1];

			/* Position absolue des persos selon la carte de l'etage */
			cellpos.x = player_pos.x - (RANGE/2) + i ;
			cellpos.y = player_pos.y - (RANGE/2) + j ;
			


							printf("vision_joueur[%d][%d] : etage[%d][%d]off_limit ? %d \n", j, i, cellpos.y, cellpos.x, !is_legal(cellpos.x, cellpos.y));

			if (((i == start && placement[0]) || (j == start && placement[1])) && is_legal(cellpos.x, cellpos.y)){
				printf("je l'ai free");
				MLV_free_image(vision_joueur[j][i]);
			}
			
			printf("[%d %d]",j,i);


			if (!is_legal(cellpos.x, cellpos.y)){
				printf("bonjour\n");

				MLV_draw_image(off_limit, CELLSIZE * i, CELLSIZE * j);
				continue;
			}

			/* Remplace l'image de la case actuel par la prochaine selon le mouvement */
			vision_joueur[j][i] = vision_joueur[next_pos.y][next_pos.x];
			MLV_draw_image(vision_joueur[j][i], CELLSIZE * i, CELLSIZE * j);

			if( i == RANGE/2  &&  j == RANGE/2 )
				MLV_draw_image(image_perso, CELLSIZE * i, CELLSIZE * j);
			/*				    MLV_actualise_window();

				    MLV_wait_keyboard(NULL,NULL,NULL);*/



		}
		printf("\n" );
	}
    
    /** LOADING **/
		printf("LOADING\n");
	/* La derniere ligne est une ligne pas presente dans l'ancien vision_joueur, on va la load */
	if(placement[1]){
		last_line = j;	/* Si le deplacement est vertical */
		for(i = 0; i < RANGE; i += 1){
			cellpos.x = player_pos.x - (RANGE/2) + i;
			cellpos.y = player_pos.y + (RANGE/2) * movement;
			if(!is_legal(cellpos.x,cellpos.y)){
								load_cell(etage,cellpos, &vision_joueur[last_line][i]);

				MLV_draw_image(off_limit, CELLSIZE * i, CELLSIZE * last_line);

			}
			else{
						printf("vision_joueur[%d][%d] -> etage[%d][%d] -> type =%d\n",last_line,i, cellpos.y,cellpos.x, position_type(etage, cellpos) ); 
				load_cell(etage, cellpos, &vision_joueur[last_line][i]); 
			MLV_draw_image(vision_joueur[last_line][i], CELLSIZE * i, CELLSIZE * last_line);
				/*    MLV_wait_keyboard(NULL,NULL,NULL);*/

		}
		}
	}
	else { 	/* Si le deplacement est horizontal */
		last_line = i;	/* Si le deplacement est horizontal */
		for(j = 0; j < RANGE; j += 1){
			cellpos.x = player_pos.x + (RANGE/2 ) * movement;
			cellpos.y = player_pos.y - (RANGE/2) + j;
			if(!is_legal(cellpos.x,cellpos.y)){
				load_cell(etage,cellpos, &vision_joueur[j][last_line]);

				MLV_draw_image(off_limit, CELLSIZE * last_line, CELLSIZE * j);

			}
			else{
						printf("vision_joueur[%d][%d] -> etage[%d][%d] \n",j, last_line, cellpos.y,cellpos.x ); 
				load_cell(etage, cellpos, &vision_joueur[j][last_line]); 
				MLV_draw_image(vision_joueur[j][last_line], CELLSIZE * last_line, CELLSIZE * j);

				/*    MLV_wait_keyboard(NULL,NULL,NULL);*/
			}
		}
	}


	 
	hud(etage);
    MLV_actualise_window();

	return 0;
}



Position absolute_pos_to_vision_pos(Floor* etage, Position pos){
	Position vision_pos;
	Position player_pos = etage->joueur.pos;
	vision_pos.x = pos.x - player_pos.x + RANGE/2;
	vision_pos.y = pos.y - player_pos.y + RANGE/2;
	return vision_pos;

}
void update_cell(Floor* etage, Position pos){
	Position vision_pos = absolute_pos_to_vision_pos(etage, pos);
	int y = vision_pos.y;
	int x = vision_pos.x;
	load_cell(etage, pos, &vision_joueur[y][x]);
	MLV_draw_image(vision_joueur[y][x], CELLSIZE * x, CELLSIZE * y);
	MLV_actualise_window();

}
void hud(Floor* etage){
	char stat_txt[999];
	Position start;
	const int nb_line = 2;
	const int marge = 3;
	Personnage pj = etage->joueur;
	Attribut stat_pj =  pj.stat;
	int portrait_size = (WINDOWS_W - BORDER_GAME) * 1/3 +1;
	MLV_draw_image( portrait,BORDER_GAME, 0);
	draw_char_bars(pj, portrait_size);
	MLV_actualise_window();

}

void draw_char_bars(Personnage pj, int portrait_size){
	Attribut stat_pj =  pj.stat;
	float xp_percent = pj.xp / xp_to_levelup(pj.level+1);
	int start_x = BORDER_GAME + portrait_size;
	int max_bar = portrait_size*2;
	int bar_h = portrait_size/3;
	MLV_free_image(bars);
	bars = MLV_create_image(max_bar, bar_h*3);

	draw_bar_on_image(bars, stat_pj.Hp, get_max_hp(stat_pj), 0, 0, bar_h, max_bar, MLV_rgba(118,205,68, 255), "HP");
	draw_bar_on_image(bars, stat_pj.Mp, get_max_mp(stat_pj), 0, bar_h, bar_h, max_bar, MLV_rgba(118,205,217, 255), "MP");
	draw_bar_on_image(bars, pj.xp, xp_to_levelup(pj.level + 1), 0, bar_h*2, bar_h, max_bar,  MLV_rgba(92,51,217, 255), "XP");
	MLV_draw_image(bars, start_x, 0);
}

void draw_bar_on_image(MLV_Image* image, int value, int max_value, int x, int y, int height, int width, MLV_Color color, const char* tag){
	float percent = value/(max_value * 1.0);
	char stat_txt[999];
	printf("%s %f %d/%d\n", tag, percent, value, max_value);
	MLV_draw_filled_rectangle_on_image(x, y, (int) (percent * (float) width), height, color, image);
	sprintf(stat_txt, "%s: %d/%d", tag, value, max_value);
	MLV_draw_text_on_image(x, y + height/2, stat_txt, MLV_COLOR_WHITE, image);

}
char cell_into_char(Celltype cell_type){
	switch(cell_type){
		case WALL: return '#';
		case ROOM: return ' ';
		case MONSTER: return '!';
		case TREASURE: return '?';
		case STAIR_UP: return '>';
		case STAIR_DOWN: return '<';
		case TREASUREO: 't';
		default : return 'Z'; /* jamais censee etre affiche */

	}
}


void affiche_floor_ascii(Floor* etage){
	unsigned int i, j;

	for (j = 0; j < FLOORH; ++j){
		for (i = 0; i < FLOORW; ++i){
			Position pos;
			pos.y = j;
			pos.x = i;
			if (etage->joueur.pos.x == pos.x && etage->joueur.pos.y == pos.y)
				printf("X");
			else
				printf("%c",cell_into_char(position_type(etage, pos)));
		}
		printf(" %d\n",j);
	}

}
