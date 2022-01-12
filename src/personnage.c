 #include "personnage.h"

Personnage creation_perso(Race race){
    Personnage pj;
    pj.race = race;
    pj.stat = init_PJ_attribut(race);
    pj.xp = 0;
    pj.level = 1;
    pj.direction = NORTH;
    int i;
    for(i = 0; i < 10; i++)
		pj.inventory[i] = NULL;
	pj.gear[0] = NULL;
	pj.gear[1] = NULL;
    
    return pj;
}

int xp_to_levelup(int level){
    return 350 + 50*level;
}
void level_up(Personnage* pj, int* stat_lvlup){
    pj->stat.Atk += stat_lvlup[0];
    pj->stat.Int += stat_lvlup[1];
    pj->stat.Def += stat_lvlup[2];
}
