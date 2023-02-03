#include <stdio.h>

#include "../include/main.h"

int main()
{
    int p[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 3, 0, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 3, 2, 0, 0, 0, 0, 0},
        {0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    showBoard(p);

    return 0;
}

void showBoard(int player[10][10])
{
    // Oben
    printf("%s", "+");
    for (int i = 0; i < 10; i++) {
        printf("%s", "-");
    }
    printf("%s\n", "+");

    //Feld
    for (int i = 0; i < 10; i++) {
        printf("%s", "|");
        for (int j = 0; j < 10; j++) {
            char tile = ' ';
            switch(player[i][j]) {
                case 0: tile = ' '; break;
                case 1: tile = 'S'; break;
                case 2: tile = 'X'; break;
                case 3: tile = 'O'; break;
            }
            printf("%c", tile);
        }
        printf("%s\n", "|");
    }

    // Unten
    printf("%s", "+");
    for (int i = 0; i < 10; i++) {
        printf("%s", "-");
    }
    printf("%s\n", "+");
}