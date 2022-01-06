#ifndef COFFRE
#define COFFRE

#include "objet.h"
typedef struct coffre{
	int opened;
	Objet* contenu;
}Coffre;

Coffre init_coffre(int etage);

#endif