
#include "coffre.h"
#include <stddef.h>

Coffre init_coffre(int etage){
	Coffre new_coffre;
	Objet obj =generate_weapon(etage);
	new_coffre.contenu[0] = obj;
	new_coffre.contenu[1] = obj;
	new_coffre.opened = 0;
	return new_coffre;
}

