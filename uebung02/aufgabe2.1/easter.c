#include <stdio.h>

int main(){
  
  int y;
  while(scanf("%d",&y)==1){
    rechnen(y);
  }
}
  
int rechnen(int Y){
  
  int G;
  int C;
  int X;
  int Z;
  int D;
  int E;
  int N;

  G = (Y % 19) + 1;
  C = (Y / 100) + 1;
  X = (3 * C / 4) - 12;
  Z = ((8 * C + 5) / 25) - 5;
  D = (5 * Y / 4) - X - 10;
  E = (11 * G + 20 + Z - X) % 30;
  if((E == 25 && G > 11)|| E == 24){
    E++;
  }
  N = 44 - E;
  if(N<21){
    N+=30;
  }
  N = N + 7 - ((D + N) % 7);
  if(N > 31){
    printf("%d - %d. April!\n",Y,N-31);
  }
  else {
    printf("%d - %d. März!\n",Y,N);
  }

  return 0;

}
