/* Play Rock Paper Scissors with the computer */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Checks if user has inputted a valid choice
int verify(const char choice[]) {
  char player = choice[0];

  if (n > 1)

  if (player == 'r') return 0;
  else if (player == 's') return 1;
  else if (player == 'p') return 2;
  else return 3;

}

//rock = 0 , scissors = 1, paper = 2
//Compares the randomly generated computer choice and the user's choice
voids compare(int n) {

  srand(time(NULL));
  int pc = rand() % 3;

  switch (n) {
    case 0:
      if (pc == 0) printf("It's a draw\n");
      else if (pc == 1) printf("You win\n");
      else printf("Computer wins\n");
      break;

    case 1:
      if (pc == 0) printf("Computer wins\n");
      else if (pc == 1) printf("It's a draw\n");
      else printf("You win\n");
      break;

    case 2:
      if (pc == 0) printf("You win\n");
      else if (pc == 1) printf("Computer wins\n");
      else printf("It's a draw\n");
      break;

      case 3:
      printf("Invalid choice\n");
  }



}


//Runs the program
int main(int n, char *args[n]) {
  setbuf(stdout, NULL);
  compare(verify(args[1]));
  //printf ("%s\n", args[1]);

}
