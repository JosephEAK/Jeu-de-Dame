#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(void){
    srand(time(NULL));
    int a, b, c, d;
    for (int i; i<10; i++){
        a = rand()%10;
        b = rand()%10;
        c = rand()%2;
        d = rand()%2;
        if (d == 1){
            d =  1;
        }else {
            d = -1;
        }
        printf("%d %d %d %d\n",a,b,c,d);
    }

    printf("\n");
    return 0;

}