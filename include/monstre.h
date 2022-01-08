#ifndef MONSTRE
#define MONSTRE

#include "cell.h"
#define MONSTER_MAX 30

typedef enum {
	ALIEN
}TypeMonstre;


typedef struct monstre{
	TypeMonstre type;
	int hp;
	int atk;
	float miss;
	float acc;
	int vitesse;

}Monstre;

Monstre init_monstre(TypeMonstre type, int dif);

#endif