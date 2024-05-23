#include <stdio.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 500
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

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

    int red_max = 0, green_max = 0, blue_max = 0;
    while ((token = strtok_r(NULL, ";", &rest)))
    {


      // e.g. 2 red, 3 blue, 8 green
      char *rest = NULL;
      char *inner_token = strtok_r(token, ",", &rest);
      while (inner_token)
      {
        int number;
        char color[10];

        if (sscanf(inner_token, " %d %9s", &number, color) == 2) {
          if (strcmp(color, "red") == 0) {
            red_max = MAX(number, red_max);
          } else if (strcmp(color, "green") == 0) {
            green_max = MAX(number, green_max);
          } else if (strcmp(color, "blue") == 0) {
            blue_max = MAX(number, blue_max);
          }
        }
        inner_token = strtok_r(NULL, ",", &rest);
      }

    }
    ret += red_max * blue_max * green_max;
  }
  printf("Answer: %d\n", ret);
  fclose(fp);
  return 0;
}
