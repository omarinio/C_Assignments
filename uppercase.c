/* Read a file and display the lines
Lines cannot be longer than max-1 characters (max-2 on Windows) */

#include <stdio.h>
#include <stdbool.h>

char *strupr(char *s) {
  int i=0;
  while(s[i]!='\0') {
      if(s[i]>='a' && s[i]<='z') {
          s[i]=s[i]-32;
      }
      ++i;
  }
  return s;
}

int main() {
    const int max = 100;
    char line[max], output[max], input[max];
    printf("The output file is: \n");
    scanf("%s", output);
    printf("The input file is: \n");
    scanf("%s", input);
    FILE *in = fopen(input, "r");
    FILE *out = fopen(output, "w");
    fgets(line, max, in);
    while (! feof(in)) {
      fprintf(out, "%s\n", strupr(line));
      fgets(line, max, in);
    }
    fclose(in);
    fclose(out);
}
