#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

int is_symbol(char c)
{
  return (c < '0' || c > '9') && c != '.';
}

int adjacent_to_symbol(char **array, int row, int start_column, int end_column, int rows, int columns)
{
  // top
  for (int i = start_column - 1; i <= end_column + 1; i++)
  {
    if (row - 1 < 0 || i < 0 || i >= columns) continue;
    if (is_symbol(array[row - 1][i]))
    {
      return 1;
    }
  }
  // bottom
  for (int i = start_column - 1; i <= end_column + 1; i++)
  {
    if (row + 1 >= rows || i < 0 || i >= columns) continue;
    if (is_symbol(array[row + 1][i]))
    {
      return 1;
    }
  }
  // left
  int left_idx = start_column - 1;
  if (left_idx >= 0 && is_symbol(array[row][left_idx]))
  {
    return 1;
  }
  // right
  int right_idx = end_column + 1;
  if (right_idx < columns && is_symbol(array[row][right_idx]))
  {
    return 1;
  }

  return 0;
}

int main(int argc, char *argv[])
{
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    fprintf(stderr, "can't open input.txt\n");
    return 1;
  }

  char buf[MAXLINE];
  int num_lines = 0, row_len = 0;
  while (fgets(buf, MAXLINE, fp) != NULL)
  {
    row_len = strlen(buf);
    num_lines++;
  }

  rewind(fp);

  char **array = malloc(num_lines * sizeof(char*));
  for (int i = 0; i < num_lines; i++)
  {
    array[i] = malloc(row_len * sizeof(char));
  }

  int line = 0;
  while (fgets(buf, MAXLINE, fp) != NULL)
  {
    buf[strcspn(buf, "\n")] = 0;
    strcpy(array[line++], buf);
  }

  fclose(fp);
  
  int ret = 0;
  for(int i = 0; i < num_lines; i++)
  {
    int start_column = -1, end_column = -1;
    for (int j = 0; j < row_len; j++)
    {
      if (isdigit((unsigned char)array[i][j]))
      {
        if (start_column == -1)
        {
          start_column = j;
        }
        end_column = j;
      }
      else if (start_column != -1 && end_column != -1)
      {
        if(adjacent_to_symbol(array, i, start_column, end_column, num_lines, row_len - 1))
        {
          int value = 0;
          sscanf(&array[i][start_column], "%d", &value);
          ret += value;
        }
        start_column = end_column = -1;
      }
    }
  }

  free(array);
  
  printf("Answer %d", ret);
  return 0;
}

