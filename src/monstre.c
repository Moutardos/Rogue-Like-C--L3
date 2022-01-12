#include <monstre.h>

Monstre init_monstre(TypeMonstre type, int dif){
	Monstre new_monstre;
	new_monstre.type = type;
	switch(type){
		case ALIEN:
			new_monstre.hp = 100;
			new_monstre.atk = 6;
			new_monstre.miss = 1;
			new_monstre.acc = 100;
			new_monstre.vitesse = 1;
	}
	new_monstre.fight = 0;
	return new_monstre;
}

void monstre_fight(Monstre* monstre, Attribut* joueur_stat){
	int roll = rand() % 101;
	int damage;
	float percent;
	
	/* AGGRO */
	if (monstre->fight == 1){
		
		/* HIT */
		if (roll > monstre->miss){
			percent = (120 - (rand() % 40))/(100 * 1.0);
						printf("percent = %f  ",percent);
			damage = (int) (monstre->atk * (float)percent );
			printf("damgage= %d  ",(int) (monstre->atk*(float)percent));
			/* CRIT */
			if(roll >= 95)
				damage = damage *3;
			
			joueur_stat->Hp -= damage;
			printf("hit ! joueur hp :%d\n", joueur_stat->Hp );
		}

					printf(" miss    ");
	}
	else {
					printf("monstre got aggroo   ");
		monstre->fight = 1;
	}
}