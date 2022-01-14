#include "cell.h"


int is_traversable(Celltype type){
	switch(type){
		case WALL :
		case TREASURE : 
		case MONSTER :
		case STAIR_DOWN: return 0;
		default : return 1;
	}
} 

int pos_is_equals(Position pos1, Position pos2){
	return pos1.x == pos2.x && pos1.y == pos2.y;
}