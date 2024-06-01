#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXLINE 1024
#define MIN(X, Y) X > Y ? Y : X;

struct seed {
  uint32_t value;
  struct seed *next;
};

struct map_item {
  uint32_t dst_start;
  uint32_t source_start;
  uint32_t range_length;
  struct map_item *next;
};

int main(int argc, char *argv[])
{
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    fprintf(stderr, "can't open input.txt\n");
    return 1;
  }

  char buf[MAXLINE];
  fgets(buf, MAXLINE, fp);
  buf[strcspn(buf, "\n")] = '\0';
  
  strtok(buf, " ");

  struct seed *list = malloc(sizeof(struct seed));
  struct seed *last = NULL;
  
  char *p;
  while ((p = strtok(NULL, " "))) {
    uint32_t num;
    sscanf(p, "%u", &num);
    if (!last) {
      list->value = num;
      last = list;
    } else {
      struct seed *new_seed = malloc(sizeof(struct seed));
      new_seed->value = num;
      new_seed->next = NULL;
      last->next = new_seed;
      last = new_seed;
    }
  };

  struct map_item *maps[7] = {NULL};
  int i = 0;
  struct map_item *map_last = NULL;
  while (fgets(buf, MAXLINE, fp)) {
    if (strchr(buf, ':')) continue;
    if (buf[0] == '\n') {
      maps[i] = malloc(sizeof(struct map_item));
      maps[i]->dst_start = -1;
      i++;
      map_last = NULL;
    } else {
      uint32_t dst, source, range;
      sscanf(buf, "%u %u %u", &dst, &source, &range);

      struct map_item *head = maps[i - 1];
      if (head->dst_start == -1) {
        head->dst_start = dst;
        head->source_start = source;
        head->range_length = range;
        map_last = head;
      } else {
        struct map_item *item = malloc(sizeof(struct map_item));
        item->dst_start = dst;
        item->source_start = source;
        item->range_length = range;
        map_last->next = item;
        map_last = item;
      }
    }
  }

  uint32_t ret = 1U << 31;

  while (list) {
    uint32_t mapped_value = list->value;
    for (int i = 0; i < 7; i++) {
      struct map_item *head = maps[i];
      while (head) {
        if (mapped_value >= head->source_start && mapped_value < head->source_start + head->range_length) {
          mapped_value = head->dst_start + mapped_value - head->source_start;
          break;
        }
        head = head->next;
      }
    }
    ret = MIN(ret, mapped_value);
    list = list->next;
  }

  printf("Answer %u\n", ret);

  fclose(fp);

  return 0;
}

