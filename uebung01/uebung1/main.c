
#include <stdio.h>
#include "numbers.h"

  int main(void){
    
    char str [12];
    printf("Enter a telephone number!\n");
    scanf("%12s",str);

    str_size = sizeof(str)/sizeof(str[0]);

    while(check_num(str)!=0){
      printf("Incorrect!\n");
      printf("Try again!\n");
      scanf("%12s",str);
      str_size = sizeof(str)/sizeof(str[0]);
    }

    print_num(str);
    printf("\n");
    return 0;
  }
