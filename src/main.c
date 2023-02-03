#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../include/main.h"

int main()
{
    srand(time(NULL));
    initGame();

    return 0;
}

// Initialisiert zwei Felder mit 0
// 0 = Leer
// 1 = Schiff
// 2 = Treffer
// 3 = Wasser (Kein Treffer)
void initGame()
{
    int player[10][10];
    int computer[10][10];

    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            player[col][row] = 0;
            computer[col][row] = 0;
        }
    }

    generateShips(player);
    generateShips(computer);

    showBoard(player, computer);
}


// Generiert ein zufälliges Schiff und Plaziert es in einem Array
void generateShips(int board[10][10])
{   
    int x, y;
    bool horizontal = true;
    bool validShip = true;
    int ships[5] = {2, 3, 3, 4, 5};

    for (int c = 0; c < 5; c++)
    {
        horizontal = rand() & 1;

        if (horizontal) {
            x = rand() % (10 - ships[c]);
            y = rand() % (10);
        } else {
            x = rand() % (10);
            y = rand() % (10 - ships[c]);
        }

        for (int j = -1; j <= 1; j++)
        {
            for (int i = -1; i < ships[c] + 1; i++)
            {
                if (horizontal) {
                    if (board[x + i][y + j] != 0) 
                    {   
                        validShip = false;
                    }
                } else {
                    if (board[x + j][y + i] != 0) 
                    {   
                        validShip = false;
                    }
                }
            }
        }

        if (!validShip) {
            validShip = true;
            c--;
            continue;
        }

        for (int i = 0; i < ships[c]; i++)
        {
            if (horizontal) {
                board[x + i][y] = 1;
            } else {
                board[x][y + i] = 1;
            }
        }
    }
}

// Zeigt zwei Felder passend Formatiert in der Konsole an
// " " = Leer
// "S" = Schiff
// "X" = Treffer
// "O" = Wasser (Kein Treffer)
void showBoard(int p1[10][10], int com[10][10])
{
    // Clear Screen
    // printf("\e[1;1H\e[2J");

    // Oben
    printf("   ABCDEFGHIJ              ABCDEFGHIJ \n");
    printf("  +----------+            +----------+\n");

    //Felder
    for (int row = 0; row < 10; row++)
    {
        printf("%2d|", row+1);
        for (int col = 0; col < 10; col++)
        {
            char tile = ' ';
            switch(p1[col][row]) {
                case 0: tile = ' '; break;
                case 1: tile = 'S'; break;
                case 2: tile = 'X'; break;
                case 3: tile = 'O'; break;
            }
            printf("%c", tile);
        }

        printf("|          %2d|", row+1);

        for (int col = 0; col < 10; col++)
        {
            char tile = ' ';
            switch(com[col][row]) {
                case 0: tile = ' '; break;
                case 2: tile = 'X'; break;
                case 3: tile = 'O'; break;
            }
            printf("%c", tile);
        }
        printf("%s\n", "|");
    }

    // Unten
    printf("  +----------+            +----------+\n");
}