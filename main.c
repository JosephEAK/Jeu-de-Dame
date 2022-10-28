#include <stdio.h>
#include <stdlib.h>

#include "dames.h"


int main (void){

	checkboard game;
	int turn = 1;

	init_checkboard(&game);
	game_update(&game, turn);

	return 0;
}

