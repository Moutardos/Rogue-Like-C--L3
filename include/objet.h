#ifndef OBJET
#define OBJET

#include "attribut.h"
typedef struct objet{
	int consomable;
	union type{
		Attribut bonus;
		/* sort */
	}
}Objet;
#endif