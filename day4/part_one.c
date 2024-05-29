#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

int main(int argc, char *argv[])
{
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    fprintf(stderr, "can't open input.txt\n");
    return 1;
  }


  int ret = 0;
  char buf[MAXLINE];
  while (fgets(buf, MAXLINE, fp) != NULL)
  {
    // skip "Card xx:"
    char *save;
    strtok_r(buf, ":", &save);
    char *left_part = strtok_r(NULL, "|", &save);

    int *winning_numbers = NULL;
    int count = 0, size = 0;
    char *s;
    char *p = strtok_r(left_part, " ", &s);
    while(p)
    {
      if (count >= size)
      {
        size = size == 0 ? 1 : size * 2;
        winning_numbers = realloc(winning_numbers, size * sizeof(int));
      }

      int number;
      sscanf(p, "%d", &number);
      winning_numbers[count++] = number;

      p = strtok_r(NULL, " ", &s);
    }

    char * right_part = strtok_r(NULL, "|", &save);

    int points = 0;
    char *p2 = strtok_r(right_part, " ", &s);
    while(p2)
    {
      int number;
      sscanf(p2, "%d", &number);
      for (int i = 0; i < count; i++)
      {
        if (winning_numbers[i] != number) continue;
        points = points == 0 ? 1 : points * 2;
      }

      p2 = strtok_r(NULL, " ", &s);
    }

    ret += points;
  }
  
  fclose(fp);

  printf("Answer %d\n", ret);

  return 0;
}

