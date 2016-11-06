#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#define NDEBUG

#include <assert.h>



/**
* generates a random number in between a specified range
* based on a time seed
* 
* @param int l - lower bound, int r - upper bound
*
*/
int generate_number(int l,int r){
  struct timeval time;

  gettimeofday(&time,NULL);

  srand ((time.tv_sec * 1000) + (time.tv_usec / 1000));

  return (l + (rand() % (r-l)));


}

/**
* sorts an array using bubble sort
* 
* @param array[] - array to be sorted, n - size of the array
*/
int bubblesort(int array[], int n){
  int i,j,tmp;
  for(i=0; i< (n-1); i++){
    for(j=0; j < n - i - 1;j++){
      if(array[j] > array[j+1]){
        tmp = array[j];
        array[j]=array[j+1];
        array[j+1]=tmp;

        assert(("Mistake at bubble!",array[j]<array[j+1]));
      }
    }
  }

  return 0;
}


/**
* quicksort for sorting an array
*
* @param arr[] - array, left - left pointrt, right - right pointer
*
*
*/
int quickSort(int arr[], int left, int right) {
  int i = left, j = right;
  assert(("Mistake at quicksort!", left <= right));
  int tmp;

  int pivot = arr[(left + right) / 2];
  
  while(i <= j){
    while(arr[i] < pivot)
      i++;
    while(arr[j] > pivot)
      j--;
    if(i <= j) {
      tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
      i++;
      j--;
    }
  };

  if(left < j)
    quickSort(arr, left , j);
  if(i < right)
    quickSort(arr, i, right);

  return 0;
}

/**
* tests if entered values are correct
* 
* @param s - lower bound, e - upper bound, n - number of random values
*/
int testScan(int s,int e, int n){
  
  if(e<s || n > e-s+1 || n<2){
    if(n > e-s+1  || n < 2){
      
      perror("n ist unpassend!!");

    }
    return 1;
  }

  return 0;

}

/**
* prints an integer - array
* 
* @param array[] -  array to be printed, n - length of array
*/
int printAry(int array[], int n){
  int i;
  for(i=0; i < n; i++){
    printf("%d ",array[i]);
  }
}


/**
* prints the usage
*
*/
int printUsage(void){
  printf("Wrong Usage!\n");
  printf("Use : sorter [-b] [-q] s e n\n");
  printf("s muss kleiner sein als e!\n");
  printf("Es sollen n Zufallszahlen generiert werden!\n");
  printf("Es müssen n Zahlen zwischen s und e passen!\n");
  printf("\n");

  return 0;
}

int main(int argc, char *argv[]){
 
  int s,e;
  int i;
  int b,q;
  b=0;
  q=0;
  

  //getting parameters b and q if possible

  for(i = 1; i<argc;i++){

    if(!strcmp(argv[i],"-b")){
      b = 1;
    }
    if(!strcmp(argv[i],"-q")){
      q = 1;
    }

  }
  //given parameters are wrong!
  if(((q==1 || b ==1) && argc-1 <= 3) || (q==1 && b==1) && argc-1<=4){
    printUsage();
    return 1;
  }


  //no display
  if(q == 1){
    printf("q!!!\n");
    return 0;
  }
  

  //setting parameters
  const int n = strtol(argv[argc-1], NULL, 10);
  e = strtol(argv[argc-2], NULL, 10);
  s = strtol(argv[argc-3], NULL, 10);
  

  //test if parameters are okay.
  if(testScan(s,e,n) == 1){
    printUsage();
    return 1;
  }
  
  
  //array with random values
  int array[n];
  

  //getting random values
  for(i=0;i<n;i++){
    array[i]=generate_number(s,e);
    usleep(1000); //sleep 1000 microseconds
    printf("%d ",array[i]);
  }
  printf("\n");

  //Bubble or quick
  if(b == 1){
    printf("Using Bubblesort!\n");
    bubblesort(array, n);
  } else{
    printf("Using Quicksort!\n");
    quickSort(array,0,n);
  }

  printf("\n");
  //prints Array
  printAry(array,n);
  printf("\n");
  return 0;





}

