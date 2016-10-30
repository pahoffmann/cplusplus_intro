
#ifndef NUMBERS_H_
#define NUMBERS_H_


/**
* prefix-size
*/
//extern int prefixsize;

/**
* suffix-size
*/
//extern int numbersize;


/**
* size of the telphone number
*/
int str_size;

//int main(void);
/**
* Functions, that checks, whether a telfon number was inserted correctly
*
* @param num_str  telephone number to be checked
* @return 1 if number incorrect, 0 otherwise
*/

int check_num(const char*);

/**
* Function which prints the new formated telephone number
* @param num_str   number to be printed
* @return 0 if succeeded
*/
void print_num(const char*);

#endif /* NUMBERS_H_ */
