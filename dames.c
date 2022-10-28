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
    //check_obligatory_move(game);
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
    printf("\n");
    show_board(game->grid);
}

void move_IA(checkboard* game){

    srand(time(NULL));
    int i, j;
    Case RAND, RAND_move;
    RAND.line = rand()%10;
    RAND.col  = rand()%10;
    RAND_move.line = 1 ;
    RAND_move.col  = rand()%2;

    if (RAND_move.col == 1){
        RAND_move.col =  1;
    }else {
        RAND_move.col = -1;
    }

    if(game->grid[RAND.line][RAND.col] == WHITE_CHECKER || CASE_VIDE){
        printf("\nCe coup n'est pas tolérer, tu ne joue pas au dame là 1\n");
    }else if ((game->grid[RAND.line+1][RAND.col-1] && game->grid[RAND.line+1][RAND.col+1]) != CASE_VIDE){
        printf("\nCe coup n'est pas tolérer, tu ne joue pas au dame là 2\n");
    }

    if ((RAND_move.line != RAND.line + 1 ) || ((RAND_move.col != RAND.col - 1) && (RAND_move.col != RAND.col + 1))){
        printf("\nCe coup n'est pas tolérer, tu ne joue pas au dame là 3\n");
    }else{
        for (i=0; i<10; i++){
            for (j=0; j<10; j++){
                if(i==RAND.line && j==RAND.col){
                    game->grid[i][j] = CASE_VIDE;
                    game->grid[RAND_move.line][RAND_move.col]= BLACK_CHECKER;
                }
            }
        }
    }
    show_board(game->grid);
}

void game_update(checkboard* game, int turn){
    int i,j;
    Case choice, move;

    if (turn == 1){
        printf("\nChoisissez un pion, sa ligne puis sa colonne : \n");
        scanf("%d %d", &choice.line, &choice.col);

        if (game->grid[choice.line][choice.col] != WHITE_CHECKER){
            printf("Tu n'as pas sélectionner de pion blanc\n");
            game_update(game, turn);
        }else if((game->grid[choice.line-1][choice.col-1] && game->grid[choice.line-1][choice.col+1]) == WHITE_CHECKER){
            printf("Ce pion ne peut pas bouger, boloss !!\n");
            game_update(game, turn);
        }

        printf("Choissisez la destination de ce pion, sa ligne puis sa colonne :\n\n");
        scanf("%d %d", &move.line, &move.col);

        if ((move.line != choice.line - 1 ) || ((move.col != choice.col - 1) && (move.col != choice.col + 1))){
            printf("\nCe coup n'est pas tolérer, tu ne joue pas au dame là\n");
            game_update(game, turn);
        }
        else{
            for (i=0; i<10; i++){
                for (j=0; j<10; j++){
                    if(i==choice.line && j==choice.col){
                        game->grid[i][j] = CASE_VIDE;
                        game->grid[move.line][move.col]= WHITE_CHECKER;
                    }
                }
            }
        }
        //check_obligatory_move(game);
        check_normal_move(game, turn);
    }else{
        move_IA(game);
        //check_obligatory_move(game);
    }

    turn = -turn;
    game_update(game, turn);
}