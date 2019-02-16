//NOY DAGAN AND ALINE KARID
#ifndef __set_h
#define __set_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char* Set;
//external sets
extern Set A;
extern Set B;
extern Set C;
extern Set D;
extern Set E;
extern Set F;
void input_decoder(char *input);//recognize the order
char* get_input();//input string
Set *my_set(char set);//recognize the set
void read_set(char *input);//input numbers to some set
void print_set(char *input);//print the set
void union_set(char *input);//put all the number of 2 set togather
void intersect_set(char *input);//the common numbers of two sets
void sub_set(char *input);//the numbers that exist in one set but not the other sets
void comp_set(char *input);//the numbers that doesnt exist in the set between the range 0-127
#endif