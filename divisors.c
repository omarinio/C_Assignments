#include <stdio.h>
#include <stdlib.h>



int main(int n, char *args[n]) {

    int mostDivisors[15];
    int highestDivisors = 0;
    int amountDivisors = 0;

    for(int i = 0; i<100; i++) {
        int counter = 0;
        for(int j = 1; j<i; j++) {
            if(i % j == 0) counter++;

        }

        if (counter > highestDivisors) {
            for (int k = 0; k<15; k++) {
                mostDivisors[k] = 0;
            }
            mostDivisors[0] = i;
            amountDivisors = 1;
            highestDivisors = counter;
        }
        else if (counter == highestDivisors) {
            mostDivisors[amountDivisors] = i;
            amountDivisors++;
        }
    }

    for(int i = 0; i<15; i++) {
        printf("%d\n", mostDivisors[i]);
    }
}
