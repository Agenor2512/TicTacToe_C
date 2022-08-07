#include "player.h"
#include "tokenLocation.h"

void initGrid();
void displayGrid();
Coordinates playerTurn(Player player);
void addToken(Coordinates coordinates, Player player);
int columnCombination(Coordinates tokenLocation);
int lineCombination(Coordinates tokenLocation);
int diagonalCombination(Coordinates tokenLocation);
int fullGrid();
void endGame(Coordinates tokenLocation);
int isLocationAvailable(Coordinates coordinates);

#define NUMBER_OF_LINES 3
#define NUMBER_OF_COLUMNS 3

char grid[NUMBER_OF_LINES][NUMBER_OF_COLUMNS];
Player player1 = {1, 'o'};
Player player2 = {2, 'x'};
