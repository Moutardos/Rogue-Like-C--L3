#include "attribut.h"
Attribut init_PJ_attribut(Race race){
	Attribut stat_PJ;
	switch(race){
		case HUMAN :
			stat_PJ.Atk = 10;
			stat_PJ.Int = 10;
			stat_PJ.Def = 10;
			break;
		case SEMI_ORC :
			stat_PJ.Atk = 25;
			stat_PJ.Int = 2;
			stat_PJ.Def = 25;
			break;
	}
	stat_PJ.Hp = get_max_hp(stat_PJ, 0); 			 
	stat_PJ.Mp = get_max_mp(stat_PJ, 0);
	return stat_PJ;
}


float rand_percent(int i, int j){
	int pourcentage = rand() % (j + 1);
	if (pourcentage < i)
		pourcentage = i;

	return (pourcentage)/100.0;
}