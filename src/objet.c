#include "objet.h"

Objet generate_weapon(int etage){
	Objet sword;
	int atk;
	int bonus;
	sword.type = WEAPON;
	sword.specificite.qualite = 1 + rand() % etage;
	atk =  10 * sword.specificite.qualite;
	bonus = atk * rand_percent(0,20);
	sword.bonus.Atk = atk + bonus;
	return sword;
}


void print_weapon(Objet weapon){
	printf("WEAPON :: \nQUALITY %d ATK %d\n\n",weapon.specificite.qualite, weapon.bonus.Atk);
} 