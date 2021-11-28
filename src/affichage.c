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
				printf("c la le prob");
				MLV_draw_image(image_perso, CELLSIZE * i, CELLSIZE * j);
			}


		}
	}
	printf("koi");
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
