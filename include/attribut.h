#ifndef ATTRIBUT
#define ATTRIBUT

typedef struct attribut {
	int Hp;               /* point de vie													       */
	int Mp;				  /* point de mana pour les sorts                                          */
	int Atk;              /* degat lors de l'utiliation d'une arme physique                        */
	int Int;              /* degat lors de l'utilisation de scroll magique       				   */
	int Def;              /* utiliser pour le calcul de pv max									   */
}Attribut;


typedef enum {
	HUMAN,
	SEMI_ORC
} Race;


typedef enum{
	Atk, Int, Def
} LvlUpStat;
/* Renvoie les attributs du personnage jouable selon sa race */
Attribut init_PJ_attribut(Race race);



/* Renvoie un pourcentage aleatoire entre i et j */
float rand_percent(int i, int j);
#endif
