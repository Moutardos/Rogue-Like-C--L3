#include "floor.h"
#include <stdlib.h>
#include <stddef.h>
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
	return etage;

}



int cell_voisine(Position* voisines, Position cellpos){
	unsigned i, j, count = 0;
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

int generate_floor(Floor* etage){
	Position voisines[4];
	Position* toexpand = (Position *) malloc(sizeof(Position) * FLOORW * FLOORH);
	Position c;
	unsigned len_expand = 0;
	unsigned len_voisines;
	unsigned pos;
	unsigned i;
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
		generate_elem(etage);
		printf("char spawn at [%d][%d]\n", etage->joueur.pos.y, etage->joueur.pos.x);

 	return 0;
}

int generate_elem(Floor* etage){
	int len = 0;
	Position* spawnable_tiles = list_of_tiles(etage,&len, 10, ROOM);
	spawn_treasure(etage, spawnable_tiles, &len);

}
int spawn_monster(Floor* etage, Position* pos_libre, int* len){

}
int spawn_treasure(Floor* etage, Position* pos_libre, int* len){
	int i;
	Position pos_rand;
	int index;
	for(i = 0; i < 5; i++){
		index = rand() % *len;
		pos_rand = pos_libre[index];
				printf("TREASURE AT %d %d\n", pos_rand.y, pos_rand.x);

		etage->map[pos_rand.y][pos_rand.x].type = TREASURE;
		etage->map[pos_rand.y][pos_rand.x].entity.coffre = init_coffre(etage->number);
		remove_pos(pos_libre, index, len);

	}
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
			if ( abs(player_pos.x - range) > range && abs(player_pos.y - range) > range){	
				pos.x = i;
				pos.y = j;
				if (position_type(etage, pos) == type){
					result[count] = pos;
					count++;
				}
				
			}
		}
	}
	*len = count;
	return result;
}

void spawn_perso(Floor * etage){
	Position stair;
	Position spawn[4];
	unsigned i = 0;
	stair.x = FLOORW/2;
	stair.y = FLOORH/2;

	cell_voisine(spawn, stair);

	while(position_type(etage, spawn[i]) == WALL)
		i++;

	etage->joueur.pos = spawn[i];
	printf("char spawn = %d %d\n", etage->joueur.pos.x, etage->joueur.pos.y);

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
int is_eligible(Floor* etage, Position cellpos){
	unsigned i, j;
	unsigned count_dist1 = 0, count_dist2 = 0;

	if( ! is_legal(cellpos.x, cellpos.y)  || position_type(etage, cellpos) == STAIR_UP)
		return 0;

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
	return x > 0 && x < FLOORW - 1 && y > 0 && y < FLOORH - 1;
}

Celltype position_type(Floor* etage, Position pos){
	return etage->map[pos.y][pos.x].type;
}
