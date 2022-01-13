
#include "coffre.h"
#include <stddef.h>

Coffre init_coffre(int etage){
	Coffre new_coffre;
	int i = rand() % 3 + 1, j;
	for(j = 0; j < i; j++) {
		new_coffre.contenu[j] = generate_objet(etage, rand() % 4);
	}
	new_coffre.nb_objet = i;
	new_coffre.opened = 0;
	return new_coffre;
}

