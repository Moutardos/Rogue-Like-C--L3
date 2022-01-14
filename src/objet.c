#include "objet.h"
#include <stdlib.h>
#include <stdio.h>
Objet generate_weapon(int etage){
	Objet sword;
	int atk;
	int bonus;
	sword.type = WEAPON;
	sword.specificite.qualite = 1 + rand() % (etage + 1);
	atk =  5 * sword.specificite.qualite;
	bonus = atk * rand_percent(0,50);
	sword.bonus.Atk = atk + bonus;
	sword.bonus.Int = 0;
	return sword;
}
void print_weapon(Objet weapon){
	printf("WEAPON :: \nQUALITY %d ATK %d\n\n",weapon.specificite.qualite, weapon.bonus.Atk);
}


Objet generate_armor(int etage){
	Objet armor;
	int def;
	int bonus;
	armor.type = ARMOR;
	armor.specificite.qualite = 1 + rand() % (etage + 1);
	def =  1 * armor.specificite.qualite;
	bonus = def * rand_percent(0,25);
	armor.bonus.Def = def + bonus;
	return armor;
}
void print_armor(Objet armor){
	printf("ARMOR :: \nQUALITY %d DEF %d\n\n", armor.specificite.qualite, armor.bonus.Def);
}

Objet generate_objet(int etage, TypeObjet type){
	Objet obj;
	obj.type = type;
	obj.specificite.qualite = 1 + rand() % (etage);
	switch(type) {
		case POTION:	obj.specificite.potion.type = rand() % 5;
						obj.specificite.potion.remaining_turn = 30; break;
		case WEAPON:	obj.bonus.Atk = (5 * obj.specificite.qualite) * (1 + rand_percent(0, 50)); 
						obj.bonus.Int = 0;
						break;
		case WAND:		obj.bonus.Int = (3 * obj.specificite.qualite) * (1 + rand_percent(0, 20));
						obj.bonus.Atk = 0;
						break;
		case ARMOR:		obj.bonus.Def = (1 * obj.specificite.qualite) * (1 + rand_percent(0, 25)); break;
	}
	return obj;
}

