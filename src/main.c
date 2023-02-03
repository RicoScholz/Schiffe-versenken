#include <stdio.h>

#include "../include/main.h"

int main()
{
    initGame();

    return 0;
}

// Initialisiert zwei Felder mit 0
// 0 = Leer
// 1 = Schiff
// 2 = Treffer
// 3 = Wasser (Kein Treffer)
void initGame() {
    int player[10][10];
    int computer[10][10];

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            player[i][j] = 0;
            computer[i][j] = 0;
        }
    }

    showBoard(player, computer);
}

// Zeigt zwei Felder passend Formatiert in der Konsole an
// 
//
//
void showBoard(int p1[10][10], int com[10][10])
{
    // Clear Screen
    printf("\e[1;1H\e[2J");

    // Oben
    printf("+----------+          +----------+\n");

    //Felder
    for (int i = 0; i < 10; i++) {
        printf("|");
        for (int j = 0; j < 10; j++) {
            char tile = ' ';
            switch(p1[i][j]) {
                case 0: tile = ' '; break;
                case 1: tile = 'S'; break;
                case 2: tile = 'X'; break;
                case 3: tile = 'O'; break;
            }
            printf("%c", tile);
        }

        printf("|          |");

        for (int j = 0; j < 10; j++) {
            char tile = ' ';
            switch(com[i][j]) {
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
    printf("+----------+          +----------+\n");
}