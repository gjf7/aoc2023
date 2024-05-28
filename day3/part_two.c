#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

struct number_pair {
  int num1;
  int num2;
};

struct number_pair* find_gear(char **array, int row, int column, int rows, int columns)
{
  
  int num_count = 0;
  struct number_pair *ret = malloc(sizeof(struct number_pair));
  // top
  if (row - 1 >= 0)
  {
    for (int i = column - 1; i >= 0 && i <= column + 1 && i < columns; i++)
    {
      if (isdigit(array[row - 1][i]))
      {
        num_count++;
        int left = i, right = i;
        while (--left >= 0 && isdigit(array[row - 1][left]));
        while (++right < columns && isdigit(array[row - 1][right]));
        int number;
        sscanf(&array[row - 1][left + 1], "%d", &number);
        if (num_count == 1)
        {
          ret->num1 = number;
        }
        else
        {
          ret->num2 = number;
        }

        i = right;
      }
    }
  }

  // bottom
  if (row + 1 < rows)
  {
    for (int i = column - 1; i >= 0 && i <= column + 1 && i < columns; i++)
    {

      if (isdigit(array[row + 1][i]))
      {
        num_count++;
        if (num_count > 2)
        {
          return NULL;
        }

        int left = i, right = i;
        while (--left >= 0 && isdigit(array[row + 1][left]));
        while (++right < columns && isdigit(array[row + 1][right]));
        int number;
        sscanf(&array[row + 1][left + 1], "%d", &number);
        if (num_count == 1)
        {
          ret->num1 = number;
        }
        else
        {
          ret->num2 = number;
        }

        i = right;
      }
    }

  }
  // left
  int left_idx = column;
  while (left_idx - 1 >= 0 && isdigit(array[row][left_idx - 1]))
  {
    left_idx--;
  }
  if (left_idx != column)
  {
    num_count++;
    if (num_count > 2)
    {
      return NULL;
    }

    int number;
    sscanf(&array[row][left_idx], "%d", &number);

    if (num_count == 1)
    {
      ret->num1 = number;
    }
    else
    {
      ret->num2 = number;
    }
  }

  // right
  int right_idx = column;
  while (right_idx + 1 < columns && isdigit(array[row][right_idx + 1]))
  {
    right_idx++;
  }
  if (right_idx != column)
  {
    num_count++;
    if (num_count > 2)
    {
      return NULL;
    }

    int number;
    sscanf(&array[row][column + 1], "%d", &number);

    if (num_count == 1)
    {
      ret->num1 = number;
    }
    else
    {
      ret->num2 = number;
    }
  }

  if (num_count == 2)
  {
    return ret;
  }

  return NULL;
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
    for (int j = 0; j < row_len; j++)
    {
      if (array[i][j] != '*') continue;
      
      struct number_pair* ptr;
      if ((ptr = find_gear(array, i, j, num_lines, row_len - 1)))
      {
        ret +=  ptr->num1 * ptr->num2;
      }
    }
  }

  free(array);
  
  printf("Answer %d", ret);
  return 0;
}

