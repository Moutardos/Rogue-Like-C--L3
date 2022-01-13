#include "test.h"
#include "floor.h"
#include "affichage.h"
#include "personnage.h"
#include "action.h"
#include "objet.h"
#include <stddef.h>
#include <stdio.h>

int test(){
	if ( ! test_floor() /* || !test_affichage() */ || !test_objet() ||  !test_action()  )
		return 0;
	return 1;
}

int test_floor(){
	Floor* etage = init_floor(creation_perso(HUMAN));
	if ( NULL == etage ){
		fprintf(stderr, "DEBUG : test_floor() error while allocuting floor ! exiting..\n");
		return 0;
	}

	if ( generate_floor(etage));

	if ( fprintf(stderr, "%d %d\n", etage->joueur.pos.x, etage->joueur.pos.y) != 6){
		fprintf(stderr, "DEBUG : test_floor() character wasn't placed on the floor ! exiting..\n");
		return 0;

	}
	free_floor(etage);  
	return 1;
}

int test_affichage(){
	Action action;
	Personnage pj = creation_perso(HUMAN);
	Floor* etage = init_floor(pj);

	generate_floor(etage);
	init_vision(etage);

	if (! init_mlv()){
		fprintf(stderr, "DEBUG : init_mlv couldn't allocate correctly ! exiting..\n");
		MLV_free_window();
		return 0;

	} 
	 

	exit_game(etage);
	return 1;
}

int test_objet(){
	int i;
	Objet sword;
	for(i = 1; i < 20; i++){
		printf("ETAGE %d    \n",i);
		sword = generate_weapon(i);
		print_weapon(sword);
	}
	return 1;
 
}

int test_action(){
	Personnage pj = creation_perso(HUMAN);
	Floor* etage = init_floor(pj);
		int stat[3] = { 0 };
	init_mlv();
	while(1){
		printf("PJ: %d ATK %d INT %d DEF\n", pj.stat.Atk,  pj.stat.Int,  pj.stat.Def);
		printf("LVLUP !!\n");
				choose_stats_lvlup(&pj, stat);
		level_up(&pj,stat);
		printf("PJ: %d ATK %d INT %d DEF\n", pj.stat.Atk,  pj.stat.Int,  pj.stat.Def);

	}
	return 1;
}