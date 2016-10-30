/******************************  nummer.c  ************************************/


/**
 * @version 29.10.16
 *  
 * @author  pahoffmann
 */

#include <stdio.h>
#include "numbers.h"

  int prefixsize;
  int numbersize;
  int str_size;

  int check_num(const char* num_str) {
    
    prefixsize=0;
    numbersize=0;
    int i=0;
    int slash=0;

    for(i=0;i<str_size;i++){
      if(num_str[i]=='/') {
        slash++;
      }
      else if(slash==0 && ((int)num_str[i]) >= (int)'0' && ((int)num_str[i]) <=(int)'9') {
        prefixsize++;
      }
      else if(slash==1 && ((int)num_str[i] >=48) && ((int)num_str[i]) <=57) {
        numbersize++;
      }

    }

    if(num_str[0] != '0') {
      printf("Wrong prefix!\n");
      return 1;
    }
    if(prefixsize < 3 || prefixsize > 5){
      printf("Wrong prefix!\n");
      return 1;
    }
    if(numbersize < 3 || numbersize >6){
      printf("Wrong Number!\n");
      return 1;
    }
    if(slash==0){
      printf("NO '/' !!!");
      return 1;
    }

    return 0;
 

  }

  void print_num(const char* num_str){
    
    int slash = 0;
    int i;
    
    printf("(");

    for(i=0;i<str_size;i++){
      if(num_str[i]=='/'){
        slash++;
        printf(")");
      }

      else if(slash==0 && ((int)num_str[i]) >= (int)'0' && ((int)num_str[i]) <=(int)'9') {
        printf("%c",num_str[i]);
      }
      else if(slash==1 && ((int)num_str[i]) >= (int)'0' && ((int)num_str[i]) <=(int)'9') {
        printf("%c",num_str[i]); 
      }
    }


  }


  
