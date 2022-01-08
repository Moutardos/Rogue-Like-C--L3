#include "test.h"
#include "floor.h"
#include "affichage.h"
#include "personnage.h"
#include "action.h"
#include <stddef.h>
#include <stdio.h>

int test(){
	if ( ! test_floor() || !test_affichage())
		return 0;
	return 1;
}

int test_floor(){
	Floor* etage = init_floor(creation_perso(HUMAN));
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
	Action action;
	Personnage pj = creation_perso(HUMAN);
	Floor* etage = init_floor(pj);

	generate_floor(etage);

	if (! init_mlv()){
		fprintf(stderr, "DEBUG : init_mlv couldn't allocate correctly ! exiting..\n");
		return 0;

	} 
	init_vision(etage);
	 
	while (1){
		affiche_floor_ascii(etage);
		treat_action(etage);
	}
	return 1;
}