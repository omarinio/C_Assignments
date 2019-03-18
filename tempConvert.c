/*Converts different temperatures*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

int choice(int n) {

}

double convert(const char choice[]) {
  for (int i = 0; i < strlen(choice) - 1; i++) {
    if (!isdigit(choice[i])) {
      return -1;
      break;
    }
  }

  double temperature  = atof(choice);
  return temperature;
}

double farenToCels(double F) {
    if (F == -1) return -1;

    double C;
    C = (5 * (F-32)) / 9;

    return C;
}

void print(double faren) {
  if (faren == -1) printf("Invalid Temperature\n");
  else printf("%lf \n", faren);
}

int main(void) {
    setbuf(stdout, NULL);

    char temp[100];
    printf("Insert the Farenheit temperature to convert --> ");
    fgets(temp,100,stdin);
    double faren = farenToCels(convert(temp));
    print(faren);
}
