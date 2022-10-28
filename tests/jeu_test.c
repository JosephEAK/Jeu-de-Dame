#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define GRIDSIZE 10

#define WHITE_CHECKER 1
#define WHITE_DAME 2
#define BLACK_CHECKER -1
#define BLACK_DAME -2
#define CASE_VIDE 0
#define IA 1
#define HUMAIN 0



typedef struct Case {
    int line;
    int col;
} Case;

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




void show_line(int i, int checkboard[GRIDSIZE][GRIDSIZE]){
    int j;
    printf(" %2d", i);
    for (j=0; j< 10; j++){
        switch(checkboard[i][j]){
            case WHITE_CHECKER : 
                printf("| W ");
                break;
            case BLACK_CHECKER :
                printf("| B ");
                break;
            /*case WHITE_DAME :
                printf("| [W] ");
                break;
            case BLACK_DAME :
                printf("| [W] ");
                break;*/
            default :
                printf("| - ");
                break;
        }
    }
    printf("|\n");
}


void show_board(int checkboard[GRIDSIZE][GRIDSIZE]){
    int i;
    printf("     0   1   2   3   4   5   6   7   8   9 \n");
    printf("   ----------------------------------------- \n");
    for (i=0; i < GRIDSIZE; i++){
        show_line (i, checkboard);
    }
    printf("   ----------------------------------------- \n");
    printf("     0   1   2   3   4   5   6   7   8   9 \n");

    printf("\n\n");
}

void init_checkboard(checkboard* game){
    
	game->nb_white = 20;
    game->nb_black = 20;

    int i, j;

    for(i=0; i<GRIDSIZE; i++){
        for (j=0; j<GRIDSIZE; j++){
            game->grid[i][j] = 0;
        }
    }

    for(i=0; i<4; i++){
        // lorsque pair mettre des pions noirs
        if(i%2 == 0){j =1;}
        else {j = 0;}

        for (j=j; j<GRIDSIZE; j+=2){
            game->grid[i][j] = BLACK_CHECKER;
        }
    }

    for(i=6; i<10; i++){
        // Lorque pair mettre des pions blancs
        if(i%2 == 0){j =1;}
        else {j = 0;}

        for (j=j; j<GRIDSIZE; j+=2){
            game->grid[i][j] = WHITE_CHECKER;
        }
    }
    show_board(game->grid);
}

void automatic_move(checkboard* game, int a, int b, int c, int d, int e, int f){

    printf("Coup obligatoire pour pour le pion L:%d C:%d -> L:%d C:%d\n", a, b, e, f);
    game->grid[a][b] = CASE_VIDE;
    game->grid[c][d] = CASE_VIDE;
    game->grid[e][f] = WHITE_CHECKER;
    printf("\n");
    check_obligatory_move(game);
}

void check_obligatory_move(checkboard* game){
    int i,j;
    
    for(i=0;i<GRIDSIZE; i++){
            for (j=0; j<GRIDSIZE; j++){
                if (game->grid[i][j] == WHITE_CHECKER){
                    if (i-1>=0 && i+1<10 && j+1<=10 && j-1>=0){
                        if (game->grid[i-1][j-1] == BLACK_CHECKER && game->grid[i-2][j-2] == CASE_VIDE && j >= 0){
                            automatic_move(game, i, j, i-1, j-1, i-2, j-2);
                        }
                        else if (game->grid[i-1][j+1] == BLACK_CHECKER && game->grid[i-2][j+2] == CASE_VIDE && j < 9){
                            automatic_move(game, i, j, i-1, j+1, i-2, j+2);
                        }
                        else if (game->grid[i+1][j+1] == BLACK_CHECKER && game->grid[i+2][j+2] == CASE_VIDE && j < 9){
                            automatic_move(game, i, j, i+1, j+1, i+2, j+2);
                        }
                        else if (game->grid[i+1][j-1] == BLACK_CHECKER && game->grid[i+2][j-2] == CASE_VIDE && j >= 9){
                            automatic_move(game, i, j, i+1, j-1, i+2, j-2);
                    }
                }
            }
        }
    }
}

void check_normal_move(checkboard* game, int turn){

    int i,j,pion,a;

    if (turn == 1){
        pion = WHITE_CHECKER;
        a = - 1;
        
    }else{
        pion = BLACK_CHECKER;
        a = 1;

    }

    for(i=0;i<GRIDSIZE; i++){
            for (j=0; j<GRIDSIZE; j++){
                if (game->grid[i][j] == pion){
                    if (i-1>=0 && i+1<=10 && j+1<=10 && j-1>=0){
                       if(game->grid[i+a][j-1] == CASE_VIDE && game->grid[i+a][j+1] == CASE_VIDE && j < 9){
                            printf("2 coups possibles pour le pion  L:%d C:%d -> L:%d C:%d ou L:%d C:%d\n", i, j, i+a, j-1, i+a, j+1);
                        }
                        else if (game->grid[i+a][j-1] == CASE_VIDE || j-1 == 0){
                            printf("1 coup  possible  pour le pion  L:%d C:%d -> L:%d C:%d\n", i, j, i+a, j-1);
                        }
                        else if (game->grid[i+a][j+1] == CASE_VIDE && j < 9){
                            printf("1 coup  possible  pour le pion  L:%d C:%d -> L:%d C:%d\n", i, j, i+a, j+1);
                    }
                }
            }
        }
    }
    printf("\n\n");
}



void game_update(checkboard* game, int turn){

    //check_obligatory_move(game);
    check_normal_move(game, turn);

    //show_board(game->grid);
    turn = -turn;
    printf("%d \n", turn);
}

int main (){

    int turn = -1, i,j;
    srand(time(NULL));
    checkboard game;

	init_checkboard(&game);


    /*for(i=0;i<GRIDSIZE; i++){

        if(i%2 == 0){j =1;}
        else {j = 0;}

        for (j=j; j<GRIDSIZE; j++){
            if (game.grid[i][j] == BLACK_CHECKER){
                game.grid[i][j] = (rand()%2)-1;
            }
        }
    }*/

    

    show_board(game.grid);

    game_update(&game, turn);
    

	return 0;

}