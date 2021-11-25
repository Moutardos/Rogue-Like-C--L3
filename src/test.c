#include "test.h"
#include "floor.h"
#include "affichage.h"
#include "personnage.h"

#include <stddef.h>
#include <stdio.h>

int test(){
	if ( ! test_floor() )
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