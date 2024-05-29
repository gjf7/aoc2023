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



  char buf[MAXLINE];
  int num_lines = 0;
  while (fgets(buf, MAXLINE, fp))
  {
    num_lines++;
  }

  int notebook[num_lines];
  for (int i = 0; i < num_lines; i++)
  {
    notebook[i] = 1;
  }

  rewind(fp);

  int current_card = 0;
  while (fgets(buf, MAXLINE, fp) != NULL)
  {
    // skip "Card xx:"
    char *save;
    strtok_r(buf, ":", &save);
    char *left_part = strtok_r(NULL, "|", &save);

    int *winning_numbers = NULL;
    int count = 0, size = 0;
    char *save2;
    char *p = strtok_r(left_part, " ", &save2);
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

      p = strtok_r(NULL, " ", &save2);
    }

    char * right_part = strtok_r(NULL, "|", &save);

    int match_count = 0;
    char *save3;
    char *p2 = strtok_r(right_part, " ", &save3);
    while(p2)
    {
      int number;
      sscanf(p2, "%d", &number);
      for (int i = 0; i < count; i++)
      {
        if (winning_numbers[i] != number) continue;
        match_count++;
      }

      p2 = strtok_r(NULL, " ", &save3);
    }

    for (int i = 1; i <= match_count; i++)
    {
      notebook[current_card + i] += notebook[current_card];
    }
    current_card++;
  }
  
  fclose(fp);
  
  int ret = 0;
  for (int i = 0; i < num_lines; i++)
  {
    ret += notebook[i];
  }
  printf("Answer %d\n", ret);

  return 0;
}

