#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------
//Constants for the 4 different states on the board
//W for water, O for miss, B for battleship and X for hit
enum state { W, O, V_3, H_4, X };
typedef enum state state;

//States the different players in the game, P1 and P2 being player 1 and 2
//respectively and None being used in the checkWin condition to show that
//no player has won the game
enum player { P1, P2, None };
typedef enum player player;

//Checks validity of the input
enum validity { Unchecked, BadFormat, BadLetter, BadDigit, BadCell, OK,
TooHigh, TooLeft };
typedef enum validity validity;




//Game object containing amount of moves made as well as the grid layout
struct game {
    int moves;
    player next;
    state grid1[9][9];
    state grid2[9][9];
};
typedef struct game game;

//-----------------------------------------------------------------------------

//Initialises the game board with all Water blocks
void startGame(game *g, player first) {
    g -> moves = 0;
    g -> next = first;
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        g -> grid1[i][j] = W;
      }
    }
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        g -> grid2[i][j] = W;
      }
    }
}

//Converts all possible row inputs so that it can fit into an array
int row(char *text) {
    char row = text[0];

    if (row == 'a') return 0;
    else if (row == 'b') return 1;
    else if (row == 'c') return 2;
    else if (row == 'd') return 3;
    else if (row == 'e') return 4;
    else if (row == 'f') return 5;
    else if (row == 'g') return 6;
    else if (row == 'h') return 7;
    else if (row == 'i') return 8;
    else return -1;
}

//Converts all possible column inputs so it can fit into an array
int col(char *text) {
    char col = text[1];

    if (col == '1') return 0;
    else if (col == '2') return 1;
    else if (col == '3') return 2;
    else if (col == '4') return 3;
    else if (col == '5') return 4;
    else if (col == '6') return 5;
    else if (col == '7') return 6;
    else if (col == '8') return 7;
    else if (col == '9') return 8;
    else return -1;
}

//Checks validity of an input as well as checking if the cell that has been
//input is available
validity valid(game *g, char *text) {
    if (strlen(text) != 2) return BadFormat;

    int r = row(text);
    int c = col(text);

    if (r == -1) return BadLetter;
    else if (c == -1) return BadDigit;

    if (g->next == P1) {
      if (g->grid1[r][c] == X || g->grid1[r][c] == O) return BadCell;
    }
    else if (g->next == P2) {
      if (g->grid2[r][c] == X || g->grid2[r][c] == O) return BadCell;
    }
    return OK;

}

//Player chooses where to place their ship
//The ship placement starts at the bottom most block for vertical ships
//and the left most for horizontal ships
validity choiceV_3(game *g, int r, int c) {
    if (g->next == P1) {
      if (c == 0 || c == 1) return TooHigh;
      for (int i = c; i < c+3; i++) {
        g->grid1[r][i] = V_3;
      }
      g->next = P2;
      g->moves++;
      return OK;
    }

    else if (g->next == P2) {
      if (c == 0 || c == 1) return TooHigh;
      for (int i = c; i < c+3; i++) {
        g->grid2[r][i] = V_3;
      }
      g->next = P1;
      g->moves++;
      return OK;
    }

    return OK;

}

validity choiceH_4(game *g, int r, int c) {
    if (g->next == P1) {
      if (r == 0 || r == 1 || r == 2) return TooLeft;
      for (int i = r; i < r+4; i++) {
        if(g->grid1[i][c] == V_3) return BadCell;
      }
      for (int i = r; i < r+4; i++) {
        g->grid1[i][c] = H_4;
      }
      g->next = P2;
      g->moves++;
      return OK;
    }

    else if (g->next == P2) {
      if (c == 0 || c == 1 || r == 2) return TooLeft;
      for (int i = r; i < r+4; i++) {
        if(g->grid2[i][c] == V_3) return BadCell;
      }
      for (int i = r; i < r+4; i++) {
        g->grid2[i][c] = H_4;
      }
      g->next = P1;
      g->moves++;
      return OK;
    }

    return OK;
}

//Each player's turn, determines whether it's a hit or a miss
void turn(game *g, int r, int c) {
    if (g->next == P1) {
      if (g->grid2[r][c] == V_3 || g->grid2[r][c] == H_4) {
        g->grid2[r][c] = X;
        printf("It's a hit!\n");
        g->next = P2;
      }
      else if (g->grid2[r][c] == W){
        g->grid2[r][c] = O;
        printf("It's a miss!\n");
        g->next = P2;
      }


    }
    else if (g->next == P2) {
      if (g->grid1[r][c] == V_3 || g->grid1[r][c] == H_4) {
        g->grid1[r][c] = X;
        printf("It's a hit!\n");
        g->next = P1;
      }
      else if (g->grid2[r][c] == W) {
        g->grid1[r][c] = O;
        printf("It's a miss!\n");
        g->next = P1;
      }

    }

}

//Checks win conditions for both players
player checkWinP1(game *g) {

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (g->grid2[i][j] == V_3 || g->grid2[i][j] == H_4 ) {
          return None;
          break;
        }
      }
    }
    return P1;
}

player checkWinP2(game *g) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (g->grid1[i][j] == V_3 || g->grid1[i][j] == H_4 ) {
          return None;
          break;
        }
      }
    }
    return P2;
}

//-----------------------------------------------------------------------------


void testNew(game *g) {
    startGame(g, P1);
    // Test a few of the cells (all should be filled with N).
    assert(g->grid1[0][0] == W);
    assert(g->grid2[8][8] == W);
    assert(g->grid1[5][7] == W);
    assert(g->grid2[2][8] == W);
    assert(g->next == P1);
    assert(g->moves == 0);
    // Test g->next isn't always set to X
    startGame(g, P2);
    assert(g->next == P2);
}

void testRowCol() {
    assert(row("a3") == 0);
    assert(row("f2") == 5);
    assert(row("i5") == 8);
    assert(col("d1") == 0);
    assert(col("b5") == 4);
    assert(col("f9") == 8);
}

void testValidity(game *g) {
    startGame(g, P1);
    assert(valid(g, "z5") == BadLetter);
    assert(valid(g, "8g") == BadLetter);
    assert(valid(g, "a0") == BadDigit);
    assert(valid(g, "a1a") == BadFormat);
    assert(valid(g, "") == BadFormat);
}

void testChoice(game *g) {
    startGame(g, P1);
    assert(choiceV_3(g, row("a2"), col("a2")) == TooHigh);
    assert(choiceH_4(g, row("a2"), col("a2")) == TooLeft);
    assert(choiceV_3(g, row("c5"), col("c5")) == OK);
    assert(choiceH_4(g, row("d5"), col("d5")) == OK);
}

void testTurn(game *g) {
    startGame(g, P1);
    choiceV_3(g, row("c5"), col("c5"));
    choiceH_4(g, row("d5"), col("d5"));
    assert(g->grid1[2][4] == V_3);
    assert(g->grid2[3][4] == H_4);
    assert(g->grid2[4][4] == H_4);
    assert(g->grid2[5][4] == H_4);
    assert(g->grid2[6][4] == H_4);
    turn(g, row("d5"), col("d5"));
    assert(g->next == P2);
    assert(g->grid2[3][4] == X);
    turn(g, row("g1"), col("g1"));
    assert(g->next == P1);
    assert(g->grid1[6][0] == O);
}

void test() {
    game *g = malloc(sizeof(game));
    testNew(g);
    testRowCol();
    testValidity(g);
    testChoice(g);
    testTurn(g);
    free(g);
    printf("All tests passed\n");
}

//-----------------------------------------------------------------------------

// Print a validity error message.
void printInvalid(validity v) {
    if (v == BadFormat) printf("Type a letter and a digit");
    else if (v == BadLetter) printf("Type a letter a, b or c");
    else if (v == BadDigit) printf("Type a digit 1, 2 or 3");
    else if (v == BadCell) printf("Choose an empty cell");
    else if (v == TooLeft) printf("Too far left");
    else if (v == TooHigh) printf("Too high up");
    printf("\n");
}

//Asks for the input
void ask(game *g, char text[100]) {
  for (int i = 1; i>0; i++) {
    printf("Input your choice: ");
    scanf("%s", text);
    if(valid(g, text) != OK) {
      printInvalid(valid(g,text));
      //continue;
    }
    else break;
  }


}

void askH(game *g, char text[100]) {
  for (int i = 1; i>0; i++) {
    printf("Input your H_4: ");
    scanf("%s", text);
    if(choiceH_4(g, row(text), col(text)) != OK) {
      printInvalid(valid(g,text));
      continue;
    }
    else break;
  }
}

void askV(game *g, char text[100]) {
  for (int i = 1; i>0; i++) {
    printf("Input your V_3: ");
    scanf("%s", text);
    if(choiceV_3(g, row(text), col(text)) != OK) {
      printInvalid(valid(g,text));
      continue;
    }
    else break;
  }
}


// Play the game
void play(char player) {
    char input[100];
    game game;
    startGame(&game, player);

    askV(&game, input);
    choiceV_3(&game, row(input), col(input));
    askV(&game, input);
    choiceV_3(&game, row(input), col(input));
    askH(&game, input);
    choiceH_4(&game, row(input), col(input));
    askH(&game, input);
    choiceH_4(&game, row(input), col(input));

    while(checkWinP1(&game) == None && checkWinP2(&game) == None ) {
        ask(&game, input);
        turn(&game, row(input), col(input));
    }

    if (checkWinP1(&game) != None) printf("Player 1 wins!");
    else printf("Player 2 wins!");
}
//-----------------------------------------------------------------------------

int main(int n, char *args[n]) {
    if (n == 1) test();
    else if (n == 2 && strcmp(args[1],"1") == 0) play(P1);
    else if (n == 2 && strcmp(args[1],"2") == 0) play(P2);
    else {
      fprintf(stderr, "Use ./battleship to run the logic tests\n");
      fprintf(stderr, "Or ./battleship 1 or ./battleship 2 to play");
      exit(1);
    }
    return 0;
}
