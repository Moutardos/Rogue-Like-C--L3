#include "personnage.h"
#include <stdlib.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

Personnage creation_perso(Race race){
    Personnage pj;
    pj.race = race;
    pj.gear[0] = generate_weapon(1); /* arme */
    pj.gear[1] = generate_armor(1); /* armure */
    pj.stat = init_PJ_attribut(race);
    pj.xp = 0;
    pj.level = 1;
    pj.direction = NORTH;
    pj.stat.Hp = get_max_hp(pj);
    pj.stat.Mp = get_max_mp(pj);
    pj.len_inventory = 0;
    pj.len_potions = 0;
    pj.selected_item =-1;
    return pj;
}

int xp_to_levelup(int level){
    return 350 + 50*level;
}

int gain_xp(Personnage* pj, int xp){
    int xp_needed = xp_to_levelup(pj->level +1);
    int bonus_xp = is_potion_active(*pj, PAPPRENTISSAGE)? xp*0.30 : 0;
    pj->xp += xp + bonus_xp;
    if(pj->xp >= xp_needed){
        pj->xp -= xp_to_levelup(pj->level +1);
        return 1;
    } 
    return 0;
}
void level_up(Personnage* pj, int* stat_lvlup){
    pj->stat.Atk += stat_lvlup[0];
    pj->stat.Int += stat_lvlup[1];
    pj->stat.Def += stat_lvlup[2];
    pj->stat.Hp = get_max_hp(*pj);
    pj->stat.Mp = get_max_mp(*pj);
    pj->level++;
}


int hit_enemy(Personnage* pj,Monstre* monstre){
    int roll = rand() % 101;
    Attribut stat_pj = pj->stat;
    int damage;
    float percent = rand_percent(80,120);
    int crit_chance = is_potion_active(*pj,PPRECISION) ? 85 : 95;

    /* ARME PHYSIQUE */
    if (pj->gear[0].type == WEAPON)
        damage =  (int) ((stat_pj.Atk + pj->gear[0].bonus.Atk) * (float)percent);

    /* WAND */
    else if (pj->gear[0].type == WAND){
        if(stat_pj.Mp >= 20){
            pj->stat.Mp -= 20;
            damage = (int) ((stat_pj.Int + pj->gear[0].bonus.Int) * 2);
        }
        else
            return -1;
    }

    /* HIT */
    if (roll > monstre->miss || is_potion_active(*pj, PPRECISION)){
        /* Potion de precision donnne 10% de crit en plus et empeche le miss */
        if(roll >= (crit_chance)){
            damage = damage *3;
        }
            
        monstre->hp -= damage;
    }

    if(monstre->hp <= 0)
        return 1;
    return 0;

}

void drink_potion(Personnage* pj, Potion potion, int index){
    switch(potion.type){
        case PSOIN :
            pj->stat.Hp = MIN(pj->stat.Hp + 0.10 * get_max_hp(*pj), get_max_hp(*pj)); break;
        case PMAGIE :
            pj->stat.Mp = MIN(pj->stat.Mp + 0.10 * get_max_mp(*pj), get_max_mp(*pj)); break;
        default:
            if(is_potion_active(*pj, potion.type))
                return ;
            pj->active_potions[pj->len_potions] = potion;
            pj->len_potions++;
    }
    discard_item(pj, index);
}

void potion_effects(Personnage* pj){
    int i;

    for (i =0; i < pj->len_potions; i++){
        pj->active_potions[i].remaining_turn--;
        if (pj->active_potions[i].remaining_turn == 0){
            if (pj->len_potions > i + 1)
               pj->active_potions[i] = pj->active_potions[i + 1];
            pj->len_potions--;
            i--;
        }
        else if (pj->active_potions[i].type == PREGEN){
            pj->stat.Hp = MIN(pj->stat.Hp + 20, get_max_hp(*pj));
            pj->stat.Mp = MIN(pj->stat.Mp + 10, get_max_mp(*pj));

        }
    }


}
int is_potion_active(Personnage pj, TypePotion type){
    unsigned int i;
    for (i =0; i < pj.len_potions; i++){
        if (pj.active_potions[i].type == type)
            return 1;
    }
    return 0;
}

int get_max_hp(Personnage pj){
    return (pj.stat.Def + pj.gear[1].bonus.Def) * 10;
}

int get_max_mp(Personnage pj){
    if(pj.gear[0].type == WAND)
        return (pj.stat.Int + pj.gear[0].bonus.Int ) * 10 - 50;
    else
        return (pj.stat.Int) *10 -50;
}

void select_item(Personnage* pj, int nb){
    pj->selected_item = nb;
}

void get_new_item(Personnage* pj, Objet objet){
    if (pj->len_inventory < 10){
        pj->inventory[pj->len_inventory] = objet;
        pj->len_inventory++;
    }
}

void discard_item(Personnage* pj, int index){
    unsigned i;
    for(i = index; i < pj->len_inventory - 1; i++) 
        pj->inventory[i] = pj->inventory[i + 1];
    pj->len_inventory -= 1;
    pj->selected_item = -1;

}
