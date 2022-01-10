#include <monstre.h>

Monstre init_monstre(TypeMonstre type, int dif){
	Monstre new_monstre;
	new_monstre.type = type;
	switch(type){
		case ALIEN:
			new_monstre.hp = 100;
			new_monstre.atk = 2;
			new_monstre.miss = 1;
			new_monstre.acc = 100;
			new_monstre.vitesse = 1;
	}
	new_monstre.fight = 0;
	return new_monstre;
}

void monstre_fight(Monstre* monstre, Attribut* joueur_stat){
	int roll = rand() % 100;

	if (monstre->fight == 1){
		if (roll > monstre->miss){
			joueur_stat->Hp -= monstre->atk;
			printf("hit ! joueur hp :%d\n", joueur_stat->Hp );
		}
					printf(" miss    ");
	}
	else {
					printf("monstre got aggroo   ");
		monstre->fight = 1;
	}
}