#include <stdio.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 512

int main(int argc, char *argv[])
{
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    fprintf(stderr, "can't open input.txt\n");
    return 1;
  }

  int ret = 0;
  char line[MAX_CHAR_PER_LINE];
  while (fgets(line, MAX_CHAR_PER_LINE, fp) != NULL)
  {
    char *rest = NULL;
    char *token = strtok_r(line, ":", &rest);

    int game_id;
    if (!token || (sscanf(token, "Game %d:", &game_id) != 1))
    {
      continue;
    }

    int possible = 1;
    while ((token = strtok_r(NULL, ";", &rest)))
    {
      int red = 0, green = 0, blue = 0;


      // e.g. 2 red, 3 blue, 8 green
      char *rest = NULL;
      char *inner_token = strtok_r(token, ",", &rest);
      while (inner_token)
      {
        int number;
        char color[10];

        if (sscanf(inner_token, " %d %9s", &number, color) == 2) {
          if (strcmp(color, "red") == 0) {
            red = number;
          } else if (strcmp(color, "green") == 0) {
            green = number;
          } else if (strcmp(color, "blue") == 0) {
            blue = number;
          }
        }
        inner_token = strtok_r(NULL, ",", &rest);
      }

      // only 12 red cubes, 13 green cubes, and 14 blue cubes
      if (red > 12 || green > 13 || blue > 14)
      {
        possible = 0;
      }
    }

    if (possible)
    {
      ret += game_id;
    }
  }
  printf("Answer: %d\n", ret);
  fclose(fp);
  return 0;
}
