#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "prototypes.h"
#include "tokenLocation.h"
#include "player.h"

/* TODO : - Demander à l'utilisateur d'entrer le numéro de la colonne où mettre son jeton
          - Afficher le jeton à l'endroit demandé par l'utilisateur
          - Demander au deuxième utilisateur d'entrer un numéro de colonne, etc
          - SI un utilisateur à aligné 3 jetons (horizontal, vertical, diagonal) ALORS afficher qu'il à gagné et arrêter le programme
          - SI aucun utilisateur n'a gagné (que la grille est remplie) ALORS afficher match nul et arrêter le programme
          -  */

int main(int argc, char const *argv[]) {
  Coordinates coordinates;

  initGrid();
  displayGrid();

  do {
    coordinates = playerTurn(player1);
    addToken(coordinates, player1);
    endGame(coordinates);

    coordinates = playerTurn(player2);
    addToken(coordinates, player2);
    endGame(coordinates);

  } while (1);

  return 0;
}

void initGrid() {
  char lines, columns;

  for (lines = 0; lines < NUMBER_OF_LINES; lines++)
    for (columns = 0; columns < NUMBER_OF_COLUMNS; columns++)
      grid[lines][columns] = ' ';
}

void displayGrid() {
  char lines, columns;

  puts("  1 2 3");

  for (lines = 0; lines < NUMBER_OF_LINES; lines++) {
    printf("%d", lines+1);
    for (columns = 0; columns < NUMBER_OF_COLUMNS; columns++) {
      printf("|%c", grid[lines][columns]);
    }
  printf("|\n");
  }
}

// Demander les coordonnées du jeton, placer le jeton dans la grille et afficher la grille
Coordinates playerTurn(Player player) {
  int columnChoice, lineChoice;
  Coordinates coordinates;

  do {
    printf("Entrez un choix de colonne : ");
    scanf("%d", &columnChoice);



    while (columnChoice < 1 || columnChoice > NUMBER_OF_COLUMNS) {
      puts("Cette coordonnée n'est pas valide. Entrez un choix valide : ");
      scanf("%d", &columnChoice);
    }
    columnChoice = columnChoice-1;

    printf("Entrez un choix de ligne : ");
    scanf("%d", &lineChoice);

    while (lineChoice < 1 || lineChoice > NUMBER_OF_LINES) {
      puts("Cette coordonnée n'est pas valide. Entrez un choix valide : ");
      scanf("%d", &lineChoice);
    }
    lineChoice = lineChoice-1;

    coordinates.columnIndex = columnChoice;
    coordinates.lineIndex = lineChoice;

  } while(isLocationAvailable(coordinates) != 1);

  return coordinates;
}

void addToken(Coordinates coordinates, Player player) {
    grid[coordinates.lineIndex][coordinates.columnIndex] = player.token;
    displayGrid();

}

int isLocationAvailable(Coordinates coordinates) {
  if (grid[coordinates.lineIndex][coordinates.columnIndex] != ' ') {
    printf("Choisissez un autre emplacement.");
    return 0;
  }
  return 1;
}

int columnCombination(Coordinates tokenLocation) {
  char playedToken = grid[tokenLocation.lineIndex][tokenLocation.columnIndex];

  if (tokenLocation.lineIndex == 0 &&
      playedToken == grid[tokenLocation.lineIndex+1][tokenLocation.columnIndex] &&
      playedToken == grid[tokenLocation.lineIndex+2][tokenLocation.columnIndex]) {
    return 1;
  }
  if (tokenLocation.lineIndex == 1 &&
      playedToken == grid[tokenLocation.lineIndex-1][tokenLocation.columnIndex] &&
      playedToken == grid[tokenLocation.lineIndex+1][tokenLocation.columnIndex]) {
    return 1;
  }
  if (tokenLocation.lineIndex == 2 &&
      playedToken == grid[tokenLocation.lineIndex-1][tokenLocation.columnIndex] &&
      playedToken == grid[tokenLocation.lineIndex-2][tokenLocation.columnIndex]) {
    return 1;
  }
  return 0;
}

int lineCombination(Coordinates tokenLocation) {
  char playedToken = grid[tokenLocation.lineIndex][tokenLocation.columnIndex];

  if (tokenLocation.columnIndex == 0 &&
      playedToken == grid[tokenLocation.lineIndex][tokenLocation.columnIndex+1] &&
      playedToken == grid[tokenLocation.lineIndex][tokenLocation.columnIndex+2]) {
    return 1;
  }
  if (tokenLocation.columnIndex == 1 &&
      playedToken == grid[tokenLocation.lineIndex][tokenLocation.columnIndex-1] &&
      playedToken == grid[tokenLocation.lineIndex][tokenLocation.columnIndex+1]) {
    return 1;
  }
  if (tokenLocation.columnIndex == 2 &&
      playedToken == grid[tokenLocation.lineIndex][tokenLocation.columnIndex-1] &&
      playedToken == grid[tokenLocation.lineIndex][tokenLocation.columnIndex-2]) {
    return 1;
  }
  return 0;
}

int diagonalCombination(Coordinates tokenLocation) {
  char playedToken = grid[tokenLocation.lineIndex][tokenLocation.columnIndex];

  // Bas gauche
  if (tokenLocation.columnIndex == 0 && tokenLocation.lineIndex == 2 &&
      playedToken == grid[tokenLocation.lineIndex-1][tokenLocation.columnIndex+1] &&
      playedToken == grid[tokenLocation.lineIndex-2][tokenLocation.columnIndex+2]) {
    return 1;
  }
  // Bas droite
  if (tokenLocation.columnIndex == 2 && tokenLocation.lineIndex == 2 &&
      playedToken == grid[tokenLocation.lineIndex-1][tokenLocation.columnIndex-1] &&
      playedToken == grid[tokenLocation.lineIndex-2][tokenLocation.columnIndex-2]) {
    return 1;
  }
  // Haut gauche
  if (tokenLocation.columnIndex == 0 && tokenLocation.lineIndex == 0 &&
      playedToken == grid[tokenLocation.lineIndex+1][tokenLocation.columnIndex+1] &&
      playedToken == grid[tokenLocation.lineIndex+2][tokenLocation.columnIndex+2]) {
    return 1;
  }
  // Haut droite
  if (tokenLocation.columnIndex == 2 && tokenLocation.lineIndex == 0 &&
      playedToken == grid[tokenLocation.lineIndex+1][tokenLocation.columnIndex-1] &&
      playedToken == grid[tokenLocation.lineIndex+2][tokenLocation.columnIndex-2]) {
    return 1;
  }
  // Milieux
  if (tokenLocation.columnIndex == 1 && tokenLocation.lineIndex == 1 &&
      playedToken == grid[tokenLocation.lineIndex-1][tokenLocation.columnIndex-1] &&
      playedToken == grid[tokenLocation.lineIndex+1][tokenLocation.columnIndex+1]) {
    return 1;
  }
  if (tokenLocation.columnIndex == 0 && tokenLocation.lineIndex == 2 &&
      playedToken == grid[tokenLocation.lineIndex+1][tokenLocation.columnIndex+1] &&
      playedToken == grid[tokenLocation.lineIndex-1][tokenLocation.columnIndex-1]) {
    return 1;
  }
  return 0;
}

int fullGrid() {
  char lines, columns;

  for (lines = 0; lines < NUMBER_OF_LINES; lines++) {
    for (columns = 0; columns < NUMBER_OF_COLUMNS; columns++) {
      if(grid[lines][columns] == ' ') {
        return 0;
      }
    }
  }
  puts("La grille est pleine.");
  return 1;
}

void endGame(Coordinates tokenLocation) {
  int lineCombinationResult, columnCombinationResult, diagonalCombinationResult;
  int fullGridResult;

  lineCombinationResult = lineCombination(tokenLocation);
  columnCombinationResult = columnCombination(tokenLocation);
  diagonalCombinationResult = diagonalCombination(tokenLocation);
  fullGridResult = fullGrid();

  if (lineCombinationResult == 1 || columnCombinationResult == 1 || diagonalCombinationResult == 1) {
    puts("Vous avez gagné.");
    exit(0);
  }
  if (fullGridResult == 1) {
    exit(0);
  }
}
