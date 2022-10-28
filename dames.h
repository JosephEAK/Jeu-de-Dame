#ifndef DAMES_HEADER
#define DAMES_HEADER

#define GRIDSIZE 10

#define WHITE_CHECKER 1
#define WHITE_DAME 2
#define BLACK_CHECKER -1
#define BLACK_DAME -2
#define CASE_VIDE 0

typedef struct checkboard{
    int grid[GRIDSIZE][GRIDSIZE];
    int nb_white, nb_black;
}checkboard;


void show_line(int i, int checkboard[GRIDSIZE][GRIDSIZE]);
void show_board(int checkboard[GRIDSIZE][GRIDSIZE]);
void init_checkboard(checkboard* game);
void check_obligatory_move(checkboard* game);
void check_normal_move(checkboard* game, int turn);
void game_update(checkboard* game, int turn);
void automatic_move(checkboard* game, int a, int b, int c, int d, int e, int f);
void move_IA(checkboard* game);
#endif