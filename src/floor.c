#include "floor.h"
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include "affichage.h"

Floor* init_floor(Personnage pj){
	unsigned int i, j;
	Floor* etage = malloc(sizeof(Floor));
	
	if (NULL == etage)
		return NULL;

	for (j = 0; j < FLOORH; ++j)
		for (i = 0; i < FLOORW; ++i){
			if (i == FLOORW/2 && j == FLOORH/2)
				etage->map[j][i].type = STAIR_UP;
			else
				etage->map[j][i].type = WALL;
		}

	etage->joueur = pj;
	etage->number = 0;
	etage->nb_monstre = 0;
	etage->nb_coffre = 0;

	etage->monstres_pos = malloc(sizeof(Position) * MONSTER_MAX);
	return etage;

}

void free_floor(Floor *etage){
	free(etage->monstres_pos);
	free(etage);
}


int generate_floor(Floor* etage){
	Position voisines[4];
	Position* toexpand = (Position *) malloc(sizeof(Position) * FLOORW * FLOORH);
	Position c;
	int len_expand = 0;
	int  len_voisines;
	int pos;
	unsigned int i;
	srand(time(NULL));

	etage->number +=1;

	c.x = FLOORW/2;
	c.y = FLOORH/2;


	len_voisines = cell_voisine(voisines, c);
	for (i = 0; i < len_voisines; i++){
		toexpand[i] = voisines[i];
		len_expand++;
	}

	while(len_expand){
		do{
			if (len_expand ==0)
				break;
			else
				pos = rand() % len_expand;
			c = toexpand[pos];
			remove_pos(toexpand, pos, &len_expand);
		}while( ! is_eligible(etage, c));


		etage->map[c.y][c.x].type = ROOM;
		len_voisines = cell_voisine(voisines, c);

		for (i = 0; i < len_voisines; i++){
			if (  is_valid(etage, voisines[i], toexpand, len_expand)){
				toexpand[len_expand] = voisines[i];
				len_expand++;
			}
		}

	}
	spawn_perso(etage);
    printf("1char spawn at [%d][%d]\n", etage->joueur.pos.y, etage->joueur.pos.x);

    affiche_floor_ascii(etage);
		generate_elem(etage);

 	return 0;
}

Position* generate_elem(Floor* etage){
	unsigned int i;
	int len = 0;
	Position* empty_tiles = list_of_tiles(etage,&len, 4, ROOM);
	printf("1len   %d\n", len);

	for(i = 0; i < 5; i++)
		spawn_elem_in_list(etage, MONSTER, &len, empty_tiles);


	
	spawn_protected_treasure(etage, len, empty_tiles, 7);
	empty_tiles = list_of_tiles(etage, &len, 25, ROOM);
	spawn_elem_in_list(etage, STAIR_DOWN, &len, empty_tiles);
	free(empty_tiles);

}
Position spawn_elem_in_list(Floor* etage, Celltype type, int* len, Position* pos_libre){
	Position pos;
	int index;

	index = rand() % *len;
	pos = pos_libre[index];
	spawn_elem(etage, type, pos);
	remove_pos(pos_libre, index, len);
	return pos;
}

void spawn_elem(Floor* etage, Celltype type, Position pos){
	etage->map[pos.y][pos.x].type = type;
	switch(type){
		case TREASURE :
			etage->map[pos.y][pos.x].entity.coffre = init_coffre(etage->number);
			etage->nb_coffre += 1;
			break;
		case MONSTER :
			etage->map[pos.y][pos.x].entity.monstre = init_monstre(ALIEN, etage->number);
			etage->monstres_pos[etage->nb_monstre] = pos;
			etage->nb_monstre++;
			break;
		default:
		break;
	}

}


void spawn_protected_treasure(Floor* etage, int len,Position* pos_libre, int nb_salles  ){
	int i = 0;
	int j = 0;
	int countV;
	int index;
	Position voisines[4];
	Position pos;
	Position pos_monstre;
	Position* spawnable_treasure = malloc(sizeof(Position) * len);
	int len_treasure = 0;

	/* Create a list of spawnable protected treasure location */
	for(i = 0; i < len; i++){
		pos = pos_libre[i];
		countV = 0;
		cell_voisine(voisines, pos);
				printf("checking %d %d ", pos.y, pos.x);

		for (j = 0; j < 4; j++){
			if (position_type(etage, voisines[j]) == ROOM)
				countV++;
		}
		printf("i got %d voisines room", countV);
		if (countV == 1){
					printf("im good  ");
			spawnable_treasure[len_treasure] = pos;
			len_treasure++;
		}
		printf("\n");
	}
	/* Spawn them at 5 random position */

	for(i = 0; i < nb_salles; i++){
		index = rand() % len_treasure;
		pos = spawnable_treasure[index];
		pos_monstre = voisine_type(etage, pos, ROOM,0);
		spawn_elem(etage, TREASURE, pos);
		spawn_elem(etage, MONSTER, pos_monstre);
		remove_pos(spawnable_treasure, index, &len_treasure);
	}
	free(spawnable_treasure);
		free(pos_libre);

}


void spawn_perso(Floor * etage){
	Position stair;
	Position treasure;
	unsigned i = 0;
	stair.x = FLOORW/2;
	stair.y = FLOORH/2;


	/* Trouve une place pour faire apparaitre le perso */
	etage->joueur.pos = voisine_type(etage, stair, ROOM, 0);


	/* Trouve une place pour faire apparaitre le tresor */
	treasure = voisine_type(etage, stair, ROOM, 0);


	spawn_elem(etage, TREASURE, treasure);

	printf("char spawn = %d %d\n", etage->joueur.pos.x, etage->joueur.pos.y);

}

Position* list_of_tiles(Floor* etage, int* len, int range, Celltype type){
	Position* result = malloc(sizeof(Position) * FLOORW * FLOORH + 1);
	int i = 0;
	int j = 0;
	int count = 0;
	Position player_pos = etage->joueur.pos;
	Position pos;
	for(j = 0; j < FLOORH; j++){
		for (i = 0; i < FLOORW; i++){
			if ( abs(player_pos.x - i) > range || abs(player_pos.y - j) > range){
                printf("%d %d is good : %d de distance du perso",  j, i, abs(player_pos.x - range));
				pos.x = i;
				pos.y = j;
				if (position_type(etage, pos) == type){
					result[count] = pos;
					count++;
				}
				
			}
		}
	}
    printf("creation de room : %d room \n", count);
	*len = count;

	return result;
}
void remove_pos(Position* lst_pos, int index, int* len){
    unsigned i;
    for(i = index; i < *len - 1; i++) 
   		lst_pos[i] = lst_pos[i + 1];
	*len -= 1;
}

int is_valid(Floor* etage, Position cellpos, Position* toexpand, int len_expand){
	unsigned i;

	if ( ! is_eligible(etage, cellpos))
		return 0;

	for (i = 0; i < len_expand; i++){
		if (cellpos.x == toexpand[i].x && cellpos.y == toexpand[i].y)
			return 0;
	}

	return 1;

}

Position voisine_type(Floor* etage, Position pos, Celltype type, int is_joueur){
	int i = 0;
	Position voisines[4];
	Position pos_joueur = etage->joueur.pos;
	int len = cell_voisine(voisines, pos);

	for (i = 0; i < len; i++){
			/* La position du voisin est du bon type et le joueur n'y est pas OU le joueur y est et est attendu */ 
		if (position_type(etage, voisines[i]) == type && (pos_is_equals(voisines[i], pos_joueur) == is_joueur))
			break;
	}

	if (i >= len)
		return pos;

	return voisines[i];

}
int is_eligible(Floor* etage, Position cellpos){
	int i, j;
	unsigned count_dist1 = 0, count_dist2 = 0;
	if( ! is_legal(cellpos.x, cellpos.y)  || position_type(etage, cellpos) == STAIR_UP
	 	|| (cellpos.x == 0 || cellpos.x == FLOORW -1) || (cellpos.y == 0 || cellpos.y == FLOORH- 1)){

		return 0;
	}


	/* On verifie le nombre de case salle a distance 1 et 2*/
	for(i = 1, j = 0; j < 2; i -=1, j +=1){

		if( is_legal(cellpos.x + i,cellpos.y + j))
			if (etage->map[cellpos.y + j][cellpos.x + i].type != WALL)
				count_dist1++;
		if( is_legal(cellpos.x - i,cellpos.y - j))
			if (etage->map[cellpos.y - j][cellpos.x - i].type != WALL)
				count_dist1++;

		if( is_legal(cellpos.x + i*2,cellpos.y + j*2))
			if (etage->map[cellpos.y + j*2][cellpos.x + i*2].type != WALL)
				count_dist2++;
		if( is_legal(cellpos.x - i*2,cellpos.y - j*2))
			if (etage->map[cellpos.y - j*2][cellpos.x - i*2].type != WALL)
				count_dist2++;

		if (count_dist1 > 1)
			return 0;
	}

	for (i = 1; i > -2; i -= 2)
	{
	if( is_legal(cellpos.x + i,cellpos.y + j))
		if (etage->map[cellpos.y + i][cellpos.x + i].type != WALL)
			count_dist2++;
	if( is_legal(cellpos.x + i,cellpos.y - j))
		if (etage->map[cellpos.y + i][cellpos.x - i].type != WALL)
			count_dist2++;
	}

	return count_dist1 == 1 && count_dist2 <= 2;

}

int is_legal(int x, int y){
	return x >= 0 && x < FLOORW   && y >= 0 && y < FLOORH;
}

void enemy_turn(Floor* etage){
	int i;
	Position pos_monstre;
	Monstre* monstre;
	Position pos_joueur = etage->joueur.pos;
	Attribut* player_stat = &(etage->joueur.stat);
	for(i = 0; i < etage->nb_monstre; i++){
		
		pos_monstre = etage->monstres_pos[i];
		if(pos_is_equals(voisine_type(etage, pos_monstre, ROOM, 1), pos_joueur)){
			printf(" OH LA BAGARE  ");
			monstre = &(etage->map[pos_monstre.y][pos_monstre.x].entity.monstre);
			monstre_fight(monstre, player_stat); /* todo: ... probably  a better way */
		}

	}
}


int cell_voisine(Position* voisines, Position cellpos){
	int i, j, count = 0;
	Position voisine;
	for(i = 1, j = 0; j < 2; i -=1, j +=1){
		voisine.x = cellpos.x + i;
		voisine.y = cellpos.y + j;
		if( is_legal(voisine.x,voisine.y)){
			voisines[count] = voisine;
			count++;
		}
		voisine.x = cellpos.x - i;
		voisine.y = cellpos.y - j;
		if( is_legal(voisine.x,voisine.y)){
			voisines[count] = voisine;
			count++;
		}
	}
	return count;

}

Cell cell_at_pos(Floor* etage, Position pos){
	return etage->map[pos.y][pos.x];
}

Celltype position_type(Floor* etage, Position pos){
	return cell_at_pos(etage, pos).type;
}
