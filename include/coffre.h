#ifndef COFFRE
#define COFFRE

#include "objet.h"
typedef struct coffre{
	int opened;
	Objet contenu[2];
	int len_objet;
}Coffre;

Coffre init_coffre(int etage);

#endif