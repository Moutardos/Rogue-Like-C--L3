#include "floor.h"
#include <stdlib.h>
#include <stddef.h>
#include "affichage.h"
Floor* init_floor(){
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
 	return 0;
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

}
void remove_pos(Position* toexpand, int index, int* len_expand){
    unsigned i;
    for(i = index; i < *len_expand - 1; i++) 
   		toexpand[i] = toexpand[i + 1];
	*len_expand -= 1;
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
