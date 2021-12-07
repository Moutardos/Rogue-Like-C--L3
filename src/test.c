#include "test.h"
#include "floor.h"
#include "affichage.h"
#include "personnage.h"

#include <stddef.h>
#include <stdio.h>

int test(){
	if ( ! test_floor() || !test_affichage())
		return 0;
	return 1;
}

int test_floor(){
	Floor* etage = init_floor();
	if ( NULL == etage ){
		fprintf(stderr, "DEBUG : test_floor() error while allocuting floor ! exiting..\n");
		return 0;
	}

	if ( generate_floor(etage));

	if ( fprintf(stderr, "%d %d\n", etage->joueur.pos.x, etage->joueur.pos.y) != 6){
		fprintf(stderr, "DEBUG : test_floor() character wasn't placed on the floor ! exiting..\n");
		return 0;

	}
	return 1;
}

int test_affichage(){
	unsigned i;
	MLV_Image*** cell_image = malloc(sizeof(MLV_Image**) * (RANGE *2));
	Floor* etage = init_floor();

	for(i = 0; i < RANGE*2; i++)
		cell_image[i] = malloc(sizeof(MLV_Image*) * (RANGE * 2));
	generate_floor(etage);

	init_mlv(); 
	init_vision(etage, cell_image);
	printf("aa");
	MLV_wait_seconds( 6 );
	movement_vision(etage, cell_image, SOUTH);
		MLV_wait_seconds( 103 );
	return 1;
}