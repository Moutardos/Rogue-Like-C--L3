#include <monstre.h>

Monstre init_monstre(TypeMonstre type, int dif){
	Monstre new_monstre;
	new_monstre.type = type;
	switch(type){
		case ALIEN:
			new_monstre.hp = 90 + (dif*5 * rand_percent(60,100));
			new_monstre.atk = 5 + (dif*5 * rand_percent(60,100));
			new_monstre.miss = 1;
			new_monstre.acc = 1;
			new_monstre.vitesse = 1;
	}
	new_monstre.max_hp = new_monstre.hp;
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
		if (roll > monstre->acc){
			percent = rand_percent(80,120);
			damage = (int) (monstre->atk * (float)percent );
			/* CRIT */
			if(roll >= 95)
				damage = damage *3;
			
			joueur_stat->Hp -= damage;
		}

	}
	else {
					printf("monstre got aggroo   ");
		monstre->fight = 1;
	}
}