#include "test.h"
#include "floor.h"
#include "affichage.h"

#include <stddef.h>

int test(){
	if ( ! test_floor() )
		return 0;
	return 1;
}

int test_floor(){
	Floor* etage = init_floor();
	if ( NULL == etage )
		return 0;

	generate_floor(etage);
	affiche_floor_ascii(etage);
	return 1;
}