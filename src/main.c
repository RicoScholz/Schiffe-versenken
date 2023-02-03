#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../include/main.h"

int main()
{
    // Initialisiert den RNG mit einem Seed
    srand(time(NULL));

    // Deklatieren und Initialisieren der Variablen
    bool pTurn;
    int player[10][10], computer[10][10];
    int playerScore, computerScore;
    initGame(&pTurn, &playerScore, &computerScore, player, computer);

    // Gameloop
    showBoards(playerScore, computerScore, player, computer);
    while (playerScore > 0 && computerScore > 0) {
        if (pTurn)
        {
            if (playerTurn(computer))
            {
                computerScore--;
            }
            else
            {
                pTurn = !pTurn;
            }
        }
        else 
        {
            if (computerTurn(player))
            {
                playerScore--;
            }
            else
            {
                pTurn = !pTurn;
            }
        }
        showBoards(playerScore, computerScore, player, computer);
    }

    return 0;
}

// Initialisiert zwei Felder mit 0
// 0 = Leer
// 1 = Schiff
// 2 = Treffer
// 3 = Wasser (Kein Treffer)
void initGame(bool *pTurn, int *p1Score, int *p2Score, int b1[10][10], int b2[10][10])
{
    *pTurn = rand() & 1;

    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            b1[col][row] = 0;
            b2[col][row] = 0;
        }
    }

    *p1Score = generateShips(b1);
    *p2Score = generateShips(b2);
}

// Fordert den Spieler auf Koordinaten einzugeben
// Mapt Koordinaten auf das Array
bool playerTurn(int enemy[10][10])
{
    char coords[4];
    printf("Koordinaten eigeben: ");
    scanf("%3s", coords);

    int x;
    switch (coords[0])
    {
        case 'A': x = 0; break;
        case 'B': x = 1; break;
        case 'C': x = 2; break;
        case 'D': x = 3; break;
        case 'E': x = 4; break;
        case 'F': x = 5; break;
        case 'G': x = 6; break;
        case 'H': x = 7; break;
        case 'I': x = 8; break;
        case 'J': x = 9; break;
        default: break;
    }

    int y = coords[1] - '1';
    if (coords[1] = '1' && coords[2] == '0')
    {
        y = 9;
    }

    switch (enemy[x][y])
    {
        // Verfehlt
        case 0: 
            enemy[x][y] = 3;
            return false;

        // Treffer -> erneuter Schuss
        case 1: 
            enemy[x][y] = 2; 
            return true;

        // bereits getroffenes Feld -> erneuter Versuch
        default: 
            printf("Ungueltige Eingabe!\n");
            playerTurn(enemy);
            break;
    }
}

// Schießt auf ein Zufälliges Feld
bool computerTurn(int enemy[10][10])
{
    int x = rand() % 10;
    int y = rand() % 10;

    switch (enemy[x][y])
    {
        // Verfehlt
        case 0: 
            enemy[x][y] = 3;
            return false;

        // Treffer -> erneuter Schuss
        case 1: 
            enemy[x][y] = 2; 
            return true;

        // bereits getroffenes Feld -> erneuter Versuch
        default: 
            computerTurn(enemy);
            break;
    }
}

// Generiert ein zufälliges Schiff und Plaziert es in einem Array
int generateShips(int board[10][10])
{   
    int x, y, score = 0;
    bool horizontal = true;
    bool validShip = true;
    int ships[5] = {2, 3, 3, 4, 5};

    for (int c = 0; c < 5; c++)
    {
        horizontal = rand() & 1;

        if (horizontal)
        {
            x = rand() % (10 - ships[c]);
            y = rand() % (10);
        } 
        else
        {
            x = rand() % (10);
            y = rand() % (10 - ships[c]);
        }

        for (int j = -1; j <= 1; j++)
        {
            for (int i = -1; i < ships[c] + 1; i++)
            {
                if (horizontal)
                {
                    if (board[x + i][y + j] != 0) 
                    {   
                        validShip = false;
                    }
                } 
                else
                {
                    if (board[x + j][y + i] != 0) 
                    {   
                        validShip = false;
                    }
                }
            }
        }

        if (!validShip)
        {
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

        score += ships[c];
    }

    return score;
}

// Zeigt zwei Felder passend Formatiert in der Konsole an
// " " = Leer
// "S" = Schiff
// "X" = Treffer
// "O" = Wasser (Kein Treffer)
void showBoards(int s1, int s2, int b1[10][10], int b2[10][10])
{
    // Clear Screen
    // printf("\e[1;1H\e[2J");

    // Oben
    printf("   ABCDEFGHIJ              ABCDEFGHIJ \n");
    printf("  +----------+     %d     +----------+     %d\n", s1, s2);

    //Felder
    for (int row = 0; row < 10; row++)
    {
        printf("%2d|", row+1);
        for (int col = 0; col < 10; col++)
        {
            char tile = ' ';
            switch(b1[col][row]) {
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
            switch(b2[col][row]) {
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