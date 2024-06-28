#include <stdio.h>
#include <string.h>
#define MAXLINE 1024
#define N 4

int all_time[4];
int all_distance[4];

int main(){
  FILE *fp = fopen("input.txt", "r");
  if(!fp){
    printf("can't open input.txt\n");
    return 1;
  }

  char buf[MAXLINE];
  for(int i = 0; i < 2; i++){
    fgets(buf,MAXLINE,fp);
    strtok(buf," ");

    int *arr = i == 0 ? all_time : all_distance;

    for(int j = 0; j < N; j++){
      sscanf(strtok(NULL, " "), "%d", &arr[j]);
    }
  }

  int ret = 1;
  for(int i = 0; i < N; i++){
    int ways = 0;
    int time = all_time[i];
    int distance = all_distance[i];

    for(int j = 1; j < time; j++){
      if((time - j) * j > distance){
        ways++;
      }
    }
    ret *= ways;
  }


  printf("Answer: %d\n", ret);

  fclose(fp);
  return 0;
}

