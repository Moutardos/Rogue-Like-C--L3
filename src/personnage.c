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
    pj.len_inventory = 0;
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
    int roll = rand() % 101;
    Attribut stat_pj = pj.stat;
    int damage;
    float percent = rand_percent(80,120);
    
    /* ARME PHYSIQUE */
    if (pj.gear[0].type == WEAPON)
        damage =  (int) ((stat_pj.Atk + pj.gear[0].bonus.Atk) * (float)percent);

    /* WAND */
    else if (pj.gear[0].type == WAND){
        if(stat_pj.Mp >= 20)
            damage = (int) ((stat_pj.Int + pj.gear[0].bonus.Int) * 2);
        else
            return -1;
    }

    /* HIT */
    if (roll > monstre->miss){
        if(roll >= 95)
            damage = damage *3;
            
        monstre->hp -= damage;
    }

    if(monstre->hp <= 0)
        return 1;
    return 0;

}
