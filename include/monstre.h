#ifndef MONSTRE
#define MONSTRE

#define MONSTER_MAX 30
#include "attribut.h"
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
	int fight;

}Monstre;

Monstre init_monstre(TypeMonstre type, int dif);
void monstre_fight(Monstre* monstre, Attribut* joueur_stat);
#endif