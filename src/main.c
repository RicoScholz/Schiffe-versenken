#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../include/main.h"

/*
    Programmierprojekt "Schiffe versenken"
    von Zhouyi Xu, Rico Scholz
    Stand 14.02.2023
*/

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
            // Spieler ist am Zug
            if (playerTurn(computer))
            {
                // Treffer - Computer verliert Punkte
                // erneuter Zug
                computerScore--;
            }
            else
            {
                // kein Treffer, Zug beendet
                pTurn = !pTurn;
            }
        }
        else 
        {
            // Computer ist am Zug
            if (computerTurn(player))
            {
                // Treffer - Spieler verliert Punkte
                // erneuter Zug
                playerScore--;
            }
            else
            {
                // kein Treffer, Zug beendet
                pTurn = !pTurn;
            }
        }
        showBoards(playerScore, computerScore, player, computer);
    }

    if (computerScore == 0)
    {
        playerWins();
    }
    if (playerScore == 0)
    {
        computerWins();
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

    // Initialisiert beide int[][] mit 0
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            b1[col][row] = 0;
            b2[col][row] = 0;
        }
    }

    // generiert Schiffe f??r beide Spieler und speichert den Score
    *p1Score = generateShips(b1);
    *p2Score = generateShips(b2);
}

// Spielerzug
bool playerTurn(int enemy[10][10])
{
    // Fordert den Spieler auf Koordinaten einzugeben
    char coords[3] = {0, 0, 0};
    printf("Koordinaten eigeben: ");
    scanf("%3s", coords);

    // Mapt die Eingabe auf eine Koordinate
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
        default:             
            printf("Ungueltige Eingabe!\n");
            return playerTurn(enemy);
            break;
    }

    // Ascii '0' = 48
    // Ascii '1' = 49
    int y;
    if (coords[1] == 49 && coords[2] == 48) 
    {
        y = 9;
    }
    else if (coords[1] - 48 >= 1 && coords[1] - 48 <= 10 && coords[2] == 0) 
    {
        y = coords[1] - 49;
    } 
    else
    {
        printf("Ungueltige Eingabe!\n");
        return playerTurn(enemy);
    }

    // Checkt das gegnerische Feld und fuehrt den Zug aus
    switch (enemy[x][y])
    {
        // Verfehlt
        case 0: 
            enemy[x][y] = 3;
            printf("\x1b[36mKein Treffer!\x1b[0m\n");
            return false;

        // Treffer -> erneuter Schuss
        case 1: 
            enemy[x][y] = 2; 
            printf("\x1b[31mTreffer!\x1b[0m\n");
            return true;

        // bereits getroffenes Feld -> erneuter Versuch
        default: 
            printf("Feld wurde bereits getroffen!\n");
            return playerTurn(enemy);
            break;
    }
}

// Schie??t auf ein Zuf??lliges Feld
bool computerTurn(int enemy[10][10])
{
    int x = rand() % 10;
    int y = rand() % 10;

    char alph[10] = "ABCDEFGHIJ";

    switch (enemy[x][y])
    {
        // Verfehlt
        case 0: 
            enemy[x][y] = 3;
            printf("Computer: %c%d \x1b[36mKein Treffer!\x1b[0m\n", alph[x], y+1);
            return false;

        // Treffer -> erneuter Schuss
        case 1: 
            enemy[x][y] = 2;
            printf("Computer: %c%d \x1b[31mTreffer!\x1b[0m\n", alph[x], y+1); 
            return true;

        // bereits getroffenes Feld -> erneuter Versuch
        default: 
            return computerTurn(enemy);
            break;
    }
}

// Generiert ein zuf??lliges Schiff und Plaziert es in einem Array
int generateShips(int board[10][10])
{   
    int x, y, score = 0;
    bool horizontal = true;
    bool validShip = true;
    int ships[6] = {5, 4, 3, 3, 2, 2};

    // Arbeitet alle Schiffe des arrays "ships" nacheinander ab
    for (int c = 0; c < 6; c++)
    {
        // Ausrichtung wird zuf??llig bestimmt
        horizontal = rand() & 1;

        // je nach Ausrichtung aendert sich der bereich x,y in dem das Schiff plaziert werden kann
        // verhindert, dass ein Schiff ueber den Rand hinaus ragt
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

        // Testet alle umliegenden Felder f??r Jedes einzelne Feld des Schiffs
        for (int j = -1; j <= 1; j++)
        {
            for (int i = -1; i < ships[c] + 1; i++)
            {
                // Abstand zwischen einem Feld des Schiffs und einem anderen Schiff ist < 1 -> Illegale Position
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

        // Mindestens einf Feld des Schiffes ist illegal
        // Schiff wird an anderer Position getestet
        if (!validShip)
        {
            validShip = true;
            c--;
            continue;
        }

        // Plaziert das Schiff auf den entsprechenden Feldern
        for (int i = 0; i < ships[c]; i++)
        {
            if (horizontal) {
                board[x + i][y] = 1;
            } else {
                board[x][y + i] = 1;
            }
        }

        // erhoeht den Score um die laenge des Schiffs
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
    // Oben
    printf("\n");
    printf("    A B C D E F G H I J                A B C D E F G H I J \n");
    printf("  +---------------------+            +---------------------+\n");

    //Felder
    for (int row = 0; row < 10; row++)
    {
        printf("%2d| ", row+1);
        for (int col = 0; col < 10; col++)
        {
            char tile[12];
            switch(b1[col][row])
            {
                case 0: strcpy(tile, "  "); break;
                // Schiff - Gelbes S
                case 1: strcpy(tile, "\x1b[33mS \x1b[0m"); break;
                // Treffer - Rotes X
                case 2: strcpy(tile, "\x1b[31mX \x1b[0m"); break;
                // Wasser - Blaues X
                case 3: strcpy(tile, "\x1b[36mX \x1b[0m"); break;
                // Default - Leeres Feld
                default: strcpy(tile, "  "); break;
            }
            printf("%s", tile);
        }

        printf("|          %2d| ", row+1);

        for (int col = 0; col < 10; col++)
        {
            char tile[12];
            switch(b2[col][row])
            {
                case 0: strcpy(tile, "  "); break;
                // Wasser - Blaues X
                case 2: strcpy(tile, "\x1b[31mX \x1b[0m"); break;
                // Wasser - Blaues X
                case 3: strcpy(tile, "\x1b[36mX \x1b[0m"); break;
                // Default - Leeres Feld
                default: strcpy(tile, "  "); break;
            }
            printf("%s", tile);
        }
        printf("%s\n", "|");
    }

    // Unten
    printf("  +---------------------+            +---------------------+\n");
    printf("         Score: %d                          Score: %d       \n", s1, s2);
    printf("\n");
}

// Spieler gewinnt das Spiel
void playerWins()
{
    printf("Winner Winner, Chicken Dinner!");
    printf("\n");
    printf("\n");
}

// Computer gewinnt das Spiel
void computerWins()
{
    printf("Oh nein, du bist ein verlierer. Learn to play, noob!");
    printf("\n");
    printf("\n");
}