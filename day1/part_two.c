#include <stdio.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 500

struct digit {
  char *c;
  int value;
  int len;
};

struct digit all_digits[] = {
  { "zero", 0, 4 },
  { "one", 1, 3 },
  { "two", 2, 3 },
  { "three", 3, 5 },
  { "four", 4, 4 },
  { "five", 5, 4 },
  { "six", 6, 3 },
  { "seven", 7, 5 },
  { "eight", 8, 5 },
  { "nine", 9, 4 },
  { "0", 0, 1 },
  { "1", 1, 1 },
  { "2", 2, 1 },
  { "3", 3, 1 },
  { "4", 4, 1 },
  { "5", 5, 1 },
  { "6", 6, 1 },
  { "7", 7, 1 },
  { "8", 8, 1 },
  { "9", 9, 1 },
  { NULL, 0, 0 },
};

int find_digit(char *s)
{
  int s_len = strlen(s);  
  for (struct digit *digit = all_digits; digit->c != NULL; digit++) {
    if (digit->len > s_len) continue;


    int is_match = 1;
    for (int i = 0; i < digit->len; i++)
    {
      if (digit->c[i] != s[i])
      {
        is_match = 0;
        break;
      }
    }
    if (is_match) return digit->value;
  }
  return -1;
}

int main()
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
    int first_digit = -1, last_digit = -1;

    for (char *c = line; *c; c++)
    {
      first_digit = find_digit(c);
      if (first_digit != -1)
      {
        break;
      }
    }
    
    int line_len = strlen(line);
    for (char *c = line + line_len - 1; *c; c--)
    {
      last_digit = find_digit(c);
      if (last_digit != -1)
      {
        break;
      }
    }
    ret += first_digit*10 + last_digit;
  }

  fclose(fp);
  printf("Answer: %d", ret);
}


