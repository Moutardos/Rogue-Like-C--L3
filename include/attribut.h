#ifndef ATTRIBUT
#define ATTRIBUT

typedef struct attribut {
	int Hp;
	int Mp;
	int Atk;
	int Int;
	int Def;
	int Acc;
}Attribut;

typedef enum {
	HUMAN
} Race;

/* Renvoie les attributs du personnage jouable selon sa race */
Attribut init_PJ_attribut(Race race);
#endif
