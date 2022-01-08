#include <monstre.h>

Monstre init_monstre(TypeMonstre type, int dif){
	Monstre new_monstre;
	new_monstre.type = type;
	switch(type){
		case ALIEN:
			new_monstre.hp = 100;
			new_monstre.atk = 2;
			new_monstre.miss = 0.01;
			new_monstre.acc = 1;
			new_monstre.vitesse = 1;
	}
	return new_monstre;
}