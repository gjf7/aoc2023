#include <stdio.h>
#include <stdint.h>
#include <math.h>
#define MAXLINE 1024
#define N 4

int main(){
  FILE *fp = fopen("input.txt", "r");
  if(!fp){
    printf("can't open input.txt\n");
    return 1;
  }

  char buf[MAXLINE];
  uint64_t time = 0, distance = 0;
  for(int i = 0; i < 2; i++){
    fgets(buf,MAXLINE,fp);
    char *p = buf;
    uint64_t *target = i == 0 ? &time : &distance;

    while(*p){
      if(*p >= '0' && *p <= '9'){
        *target = *target * 10 + (*p - '0');
      }
      p++;
    }
  }
  
  uint64_t low = (time - sqrt(time * time - 4 * distance)) / 2;
  uint64_t high = (time + sqrt(time * time - 4 * distance)) / 2;

  printf("answer %llu\n", high - low);

  fclose(fp);
  return 0;
}

