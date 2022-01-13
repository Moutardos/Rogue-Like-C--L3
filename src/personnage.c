 #include "personnage.h"

Personnage creation_perso(Race race){
    Personnage pj;
    pj.race = race;
    pj.stat = init_PJ_attribut(race);
    pj.xp = 0;
    pj.level = 1;
    pj.direction = NORTH;
    int i;
	pj.gear[0] = generate_weapon(1); /* arme */
	pj.gear[1] = generate_armor(1); /* armure */
    
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


int hit_enemy(Personnage pj,Monstre* monstre){
    
}
