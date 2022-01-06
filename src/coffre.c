
#include "coffre.h"
#include <stddef.h>

Coffre init_coffre(int etage){
	Coffre new_coffre;
	new_coffre.contenu = NULL;
	new_coffre.opened = 0;
	return new_coffre;
}