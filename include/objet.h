#ifndef OBJET
#define OBJET

#include "attribut.h"
typedef struct objet{
	int consomable;
	Attribut bonus;
	int active;
	int remaining_turn;
}Objet;
#endif