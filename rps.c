/* Play Rock Paper Scissors with the computer */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

//Integer constants for different results and choices
enum choice {Rock, Paper, Scissors};
enum result {Win, Loss, Draw};

//Checks if user has inputted a valid choice
int verify(int n, const char choice[]) {
    char player = choice[0];
    if (n > 1) return -1;

    if (player == 'r') return Rock;
    else if (player == 's') return Scissors;
    else if (player == 'p') return Paper;
    else return -1;

}

//rock = 0 , scissors = 1, paper = 2
//Compares the randomly generated computer choice and the user's choice
int compare(int n) {

    srand(time(NULL));
    int pc = rand() % 3;

    switch (n) {
      case Rock:
        if (pc == 0) return Draw;
        else if (pc == 1) return Win;
        else return Loss;
        break;

      case Scissors:
        if (pc == 0) return Loss;
        else if (pc == 1) return Draw;
        else return Win;
        break;

      case Paper:
        if (pc == 0) return Win;
        else if (pc == 1) return Loss;
        else return Draw;
        break;
  }

    return -1;
}

//Prints the result
void print(int result) {
    if (result == Draw) printf("It's a draw\n");
    else if (result == Win) printf("You win\n");
    else if (result == Loss) printf("Computer wins\n");
    else printf("Invalid input\n");
}

//Test to check if the input is correctly identified
void testVerify() {
    assert(verify(1, "r") == Rock);
    assert(verify(1, "s") == Scissors);
    assert(verify(1, "p") == Paper);
    assert(verify(1, "t") == -1);
    assert(verify(3, "rps") == -1);
}

//Tests the verification
void test() {
    testVerify();
    printf("All tests passed\n");
}


//Runs the program
int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if (n == 1) test();
    else if (n == 2) print(compare(verify(strlen(args[1]),args[1])));
    else {
      printf("Please use ./rps to test or ./rps x \n");
      printf("where x is either r or p or s\n");
  }

}
