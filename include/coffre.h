#ifndef COFFRE
#define COFFRE

#include "objet.h"
typedef struct coffre{
	int opened;
	Objet contenu[3];
	int nb_objet;
}Coffre;

Coffre init_coffre(int etage);

#endif
