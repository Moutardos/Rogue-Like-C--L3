#include "cell.h"


int is_traversable(Celltype type){
	switch(type){
		case WALL : return 0;
		case TREASURE : return 0;
		case MONSTER : return 0;
		default : return 1;
	}
} 



