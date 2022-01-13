#include "objet.h"

Objet generate_weapon(int etage){
	Objet sword;
	int atk;
	int bonus;
	sword.type = WEAPON;
	sword.specificite.qualite = 1 + rand() % etage;
	atk =  5 * sword.specificite.qualite;
	bonus = atk * rand_percent(0,20);
	sword.bonus.Atk = atk + bonus;
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
	armor.specificite.qualite = 1 + rand() % etage;
	def =  5 * armor.specificite.qualite;
	bonus = def * rand_percent(0,20);
	armor.bonus.Def = def + bonus;
	return armor;
}
void print_armor(Objet armor){
	printf("ARMOR :: \nQUALITY %d DEF %d\n\n", armor.specificite.qualite, armor.bonus.Def);
}
