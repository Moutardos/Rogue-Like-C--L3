#ifndef AFFICHAGE
#define AFFICHAGE

#include <MLV/MLV_all.h>

#include "cell.h"
#include "floor.h"

#define WINDOWS_W 1280
#define WINDOWS_H 924
#define CELLSIZE 132/* Taille d'une cell en pixel (normalement 32) */
#define RANGE 7

#define INVENTORY_SLOT (WINDOWS_W - BORDER_GAME) / 3
#define BORDER_GAME CELLSIZE * RANGE


/* Initialise la fenetre, load les images utilise dans affichage
*/
int init_mlv();
void free_graph();

/* Load l'image qui va etre affiche dans l'ecran a la position indique */
int load_cell(Floor* etage, Position cellpos, MLV_Image** image);


/* Renvoie l'url du sprite indique */
const char* image_url(Celltype cell_type, int theme);
const char* image_url_monstre(TypeMonstre monstre);
const char* image_url_object(Objet objet);


/* Load les cellules du jeu qui vont etre affiche a l'ecran */
int init_vision(Floor* etage);

/* Refresh l'ecran de jeu */
void refresh_vision(Floor* etage);


/* Deplace toute les cellules visibles dans une direction, en gardant le joueur au millieu.
   Free les images qui ne vont plus etre utilise lors de l'affichage et load les nouvelles images
*/
int movement_vision(Floor* etage, Cardinal direction);

/* FONCTION DEBUG, renvoie un char indiquant le type de cell
*/
char cell_into_char(Celltype cell_type);


/* ca tourneeeee (a enlever)*/
void rotate_pj(Floor* etage);

/* Recoie une position dans l'etage et renvoie la position selon la vision du joueur */
Position absolute_pos_to_vision_pos(Floor* etage, Position pos);
/* Affiche l'HUD contenant les stats du perso */
void hud(Personnage pj);

/* Load et draw la cell de la case pos_abs dans l'etage en i j */
void display_cell(Floor* etage, Position pos_abs, int i, int j);
/* Affiche les trois differentes barres (mana, hp, xp) a cote
   du portrait du joueur */
void draw_char_bars(Personnage pj, int portrait_size);

/* Affiche une barre a la position indique, affichant le pourcentage de completion */
void draw_bar_on_image(MLV_Image* image, int value, int max_value, int x, int y, int height, int width, MLV_Color color, const char* tag);

/* Affiche les statistique du joueur et, si non null, l'affichage pour les augmenter apres un level up*/
void display_stat(Personnage pj, int* stat_lvlup, int curseur);

/* Affiche le menu permettant de continuer ou arreter de jouer */
void display_continue(int index);
/* Affiche le contenu de l'inventaire du joueur aux emplacements adéquats */
void draw_inventory(Personnage pj);

/* Affiche un coffre ouvert et son contenu */
void draw_chest(Objet content[], int size);

/* FONCTION DEBUG, affiche le niveau en ascii
*/
void affiche_floor_ascii(Floor* etage);
#endif
