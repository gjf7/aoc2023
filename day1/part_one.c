#include <stdio.h>

#define MAX_CHAR_PER_LINE 500

int main()
{ FILE *fp = fopen("input.txt", "r"); if (fp == NULL)
  {
    fprintf(stderr, "can't open input.txt\n");
    return 1;
  }

  int ret = 0;
  char line[MAX_CHAR_PER_LINE];

  while (fgets(line, MAX_CHAR_PER_LINE, fp) != NULL)
  {
    char* c = line;
    int first_digit = -1, last_digit = -1;

    while (*c != '\0')
    {
      int n = *(c++) - '0';
      if (n < 0 || n > 9)
      {
        continue;
      }

      if (first_digit == -1)
      {
        first_digit = last_digit = n;
      }
      else
      {
        last_digit = n;
      }
    }

    if (first_digit != -1)
    {
      ret += first_digit*10 + last_digit;
    }
  }

  fclose(fp);
  printf("Answer: %d", ret);
}


