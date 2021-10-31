#include "attribut.h"

Attribut init_PJ_attribut(Race race){
	Attribut stat_PJ;
	switch(race){
		case HUMAN :
			stat_PJ.Hp = 100;
			stat_PJ.Mp = 50;
			stat_PJ.Atk = 10;
			stat_PJ.Int = 10;
			stat_PJ.Def = 10;
			stat_PJ.Acc = 100;
	}
	return stat_PJ;
}