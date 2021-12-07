#include "affichage.h"
#include <stdio.h>

MLV_Image* image_perso;

void init_mlv(){
        MLV_create_window( "ver 0.123 !", "roguelike", WINDOWS_W, WINDOWS_H );
        image_perso = MLV_load_image("include/art/mc.png");
        MLV_resize_image(image_perso, CELLSIZE - 2, CELLSIZE - 2);
}



int load_cell( Floor* etage, Position cellpos, MLV_Image** image){
	Celltype type; 
	if (is_legal(cellpos.x, cellpos.y)){

					printf("%d %d is legal\n", cellpos.x, cellpos.y);

		type = position_type(etage, cellpos);
		printf("   type fetched");
		*image = MLV_load_image(image_url(type, 0));
				printf("   loaded");

		MLV_resize_image(*image, CELLSIZE, CELLSIZE);
						printf("   resized ");

	} 
	else{  
			printf("?");

	}
	/* else affiche carre noir */
	return 1;
}


const char* image_url(Celltype cell_type, int theme){
	/* theme represente le biome de l'etage TODO*/
	switch(cell_type){
		case WALL: return "include/art/wall01.png";
		case ROOM: return "include/art/floor03.png";
		case STAIR_DOWN: return "include/art/stairdown.png";
		case STAIR_UP: return "include/art/stairup.png";
		default : return "include/art/notfound.png";
	}
}
int init_vision(Floor* etage, MLV_Image*** cell_image){
	/* remplie case +x autour du perso*/ 
	Position pos_joueur = etage->joueur.pos;
	Position cellpos;
	unsigned i;    
	unsigned j; 
 
			printf(" rentring?  "); 

	for (j = 0; j <=RANGE; ++j){ 
		for (i = 0; i <= RANGE; ++i){

			cellpos.x = pos_joueur.x - (RANGE/2 + RANGE%2) + i;
			cellpos.y = pos_joueur.y - (RANGE/2 + RANGE%2) + j;
										printf("etat actuel :  x relatif : %d\n y relatif : %d\n", -1*(RANGE/2 + RANGE%2) + i, -1*(RANGE/2 + RANGE%2) + j );

			load_cell(etage, cellpos, &cell_image[j][i]); 
			printf("load cell survived\n");
			MLV_draw_image(cell_image[j][i], CELLSIZE * i, CELLSIZE * j);
						printf("draw survived\n");

			if( cellpos.x == pos_joueur.x && cellpos.y == pos_joueur.y){
				printf("PERSO ");
				MLV_draw_image(image_perso, CELLSIZE * i, CELLSIZE * j);
			} 


		}
	}
	MLV_actualise_window();
	return 0; 
}

int movement_vision(Floor* etage, MLV_Image*** cell_image, Cardinal direction){
	unsigned int i, j;
	unsigned int start;
	int placement[2] = {0,0}; /* [0] = x [1] = y */
	int movement;
	int last_line;
	Position pos_joueur = etage->joueur.pos;
	Position cellpos;

	if (NULL == cell_image)
		return 1;

	switch(direction){
		case NORTH : placement[1] = 1; movement = 1; start = 0; break;
		case EAST  : placement[0] = 1; movement = -1; start = RANGE; break;
		case SOUTH : placement[1] = 1; movement = -1; start = RANGE;     break;
		case WEST  : placement[0] = 1; movement =  1; start = 0;     break;
	}

	pos_joueur.x -= placement[0] * movement;
	pos_joueur.y -= placement[1] * movement;/** REMOOOOOVE **/
	
	/** SCROLLING **/
	for(j = start   ; j <= RANGE - placement[1]  && j >= 0; j += movement)
		for(i = start ; i <= RANGE - placement[0]  && i >= 0; i += movement){
			printf("cell_image[%d][%d] -> cell_image[%d][%d]\n", j,i, j + movement * placement[1], i + movement * placement[0]);			cell_image[j][i] = cell_image[j + movement * placement[1]][i + movement * placement[0]];
			MLV_draw_image(cell_image[j][i], CELLSIZE * i, CELLSIZE * j);
				MLV_wait_seconds( 1);
				    MLV_actualise_window();

		}
    
    /** LOADING **/

	/* La derniere ligne est une ligne pas presente dans l'ancien cell_image, on va la load */
	last_line = (RANGE+1) * direction;
	/* Si le deplacement est vertical */
	if(placement[1]){
		for(i = 0; i <= RANGE && i >= 0; i += 1){
			cellpos.x = pos_joueur.x - (RANGE/2 + RANGE%2) + i;
			cellpos.y = pos_joueur.y - (RANGE + 1) * direction;
			load_cell(etage, cellpos, &cell_image[last_line][i]); 
			MLV_draw_image(cell_image[last_line][i], CELLSIZE * i, CELLSIZE * last_line);
				MLV_wait_seconds( 1);
				    MLV_actualise_window();

		}
	}
	else { 	/* Si le deplacement est horizontal */
		for(j = start; j <= RANGE && j >= 0; j += movement){
			cellpos.x = pos_joueur.x + (RANGE + 1) * direction;
			cellpos.y = pos_joueur.y - (RANGE/2 + RANGE%2) + j;
			load_cell(etage, cellpos, &cell_image[j][last_line]); 
			MLV_draw_image(cell_image[j][last_line], CELLSIZE * last_line, CELLSIZE * j);
		}

	} 

    MLV_actualise_window();

	return 0;
}


char cell_into_char(Celltype cell_type){
	switch(cell_type){
		case WALL: return '#';
		case ROOM: return ' ';
		case MONSTER: return '!';
		case TREASURE: return '?';
		case STAIR_UP: return '>';
		case STAIR_DOWN: return '<';
	}
	return '1'; /* jamais censee etre affiche */
}


void affiche_floor_ascii(Floor* etage){
	unsigned int i, j;

	for (j = 0; j < FLOORH; ++j){
		for (i = 0; i < FLOORW; ++i){
			Position pos;
			pos.y = j;
			pos.x = i;
			printf("%c",cell_into_char(position_type(etage, pos)));
		}
		printf("\n");
	}

}
