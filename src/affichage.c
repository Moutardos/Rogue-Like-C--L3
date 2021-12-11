#include "affichage.h"
#include <stdio.h>

MLV_Image* image_perso;
MLV_Image* background;

void init_mlv(){
        MLV_create_window( "ver 0.123 !", "roguelike", WINDOWS_W, WINDOWS_H );
        image_perso = MLV_load_image("include/art/mc.png");
        background = MLV_load_image("include/art/bg.png");
        MLV_resize_image(image_perso, CELLSIZE , CELLSIZE );
        MLV_resize_image(background, CELLSIZE , CELLSIZE );
}



int load_cell( Floor* etage, Position cellpos, MLV_Image** image){
	Celltype type; 
	if (is_legal(cellpos.x, cellpos.y)){


		type = position_type(etage, cellpos);
		if( type != ROOM && type != WALL){ /* type transparent */
			*image = MLV_load_image(image_url(ROOM,0)); 
			MLV_draw_image_on_image(MLV_load_image(image_url(type,0)), *image, 0,0);
		}
		else
			*image = MLV_load_image(image_url(type, 0));

		MLV_resize_image(*image, CELLSIZE, CELLSIZE);

	} 
	else{  
		*image = background;

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
 

	for (j = 0; j <RANGE; ++j){ 
		for (i = 0; i <RANGE; ++i){

			cellpos.x = pos_joueur.x - (RANGE/2 + RANGE%2) + i + 1; /* hard value +1, je sais pas pourquoi ... */
			cellpos.y = pos_joueur.y - (RANGE/2 + RANGE%2) + j + 1;

			load_cell(etage, cellpos, &cell_image[j][i]); 
			MLV_draw_image(cell_image[j][i], CELLSIZE * i, CELLSIZE * j);

			if( cellpos.x == pos_joueur.x && cellpos.y == pos_joueur.y){
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
	int decalage_y, decalage_x;

	Position cellpos;

	if (NULL == cell_image)
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
			
			if ((i == start && placement[0]) || (j == start && placement[1]))
				MLV_free_image(cell_image[j][i]);
			printf("[%d %d]",j,i);
			cell_image[j][i] = cell_image[j + movement * placement[1]][i + movement * placement[0]];
			MLV_draw_image(cell_image[j][i], CELLSIZE * i, CELLSIZE * j);

			if( i == RANGE/2  &&  j == RANGE/2 )
				MLV_draw_image(image_perso, CELLSIZE * i, CELLSIZE * j);

		}
		printf("\n" );
	}
    
    /** LOADING **/
		printf("LOADING\n");
	/* La derniere ligne est une ligne pas presente dans l'ancien cell_image, on va la load */
	if(placement[1]){
		last_line = j;	/* Si le deplacement est vertical */
		for(i = 0; i < RANGE; i += 1){
			cellpos.x = etage->joueur.pos.x - (RANGE/2 + RANGE%2) + i +1;
			cellpos.y = etage->joueur.pos.y + RANGE/2 * movement;
						printf("cell_image[%d][%d] -> pos_joueur + range = %d\n", cellpos.y,cellpos.x, etage->joueur.pos.y + RANGE*movement); 
			load_cell(etage, cellpos, &cell_image[last_line][i]); 
			MLV_draw_image(cell_image[last_line][i], CELLSIZE * i, CELLSIZE * last_line);

		}
	}
	else { 	/* Si le deplacement est horizontal */
		last_line = i;	/* Si le deplacement est horizontal */
		for(j = 0; j < RANGE; j += 1){
			cellpos.x = etage->joueur.pos.x + RANGE/2* movement;
			cellpos.y = etage->joueur.pos.y - (RANGE/2 + RANGE%2) + j +1;
						printf("cell_image[%d][%d] -> pos_joueur + range = %d\n", cellpos.y,cellpos.x, etage->joueur.pos.x + RANGE*movement); 

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
