//NOY DAGAN AND ALINE KARID
#include "set.h"
#pragma warning (disable:4996)
//defined external varible
char empty = '\0';
Set A = &empty;
Set B = &empty;
Set C = &empty;
Set D = &empty;
Set E = &empty;
Set F = &empty;

//input string
char* get_input()
{
	char *s = malloc(1);//allocation string
	int c;
	int i = 0;
	while ((c = getchar()) != '\n')//input until underline
	{
		s[i++] = c;//input characters to the string
		s = realloc(s, i + 1);//bigger the allocation in one for char after char
	}
	s[i] = '\0';
	return s;
}
//recognize the order
void input_decoder(char *input)
{
	char command[14] = { '\0' };//string for order
	int i = 0;
	if (strlen(input) < 1) {//if not enter command
		printf("Please enter command\n");
	}
	else {
		for (; input[i] != ' ' && i != 14; i++)//set the order
			command[i] = input[i];
		input = input + i;
		if (strcmp(command, "read_set") == 0) {
			read_set(input);
		}
		else if (strcmp(command, "print_set") == 0) {
			print_set(input);
		}
		else if (strcmp(command, "union_set") == 0) {
			union_set(input);
		}
		else if (strcmp(command, "intersect_set") == 0) {
			intersect_set(input);
		}
		else if (strcmp(command, "sub_set") == 0) {
			sub_set(input);
		}
		else if (strcmp(command, "comp_set") == 0) {
			comp_set(input);
		}
		else {
			printf("No such command\n");
		}
	}
}
Set *my_set(char set)//recognize the set
{
	return set == 'A' ? &A : set == 'B' ? &B : set == 'C' ? &C : set == 'D' ? &D : set == 'E' ? &E : set == 'F' ? &F : NULL;
}
//input numbers to some set
void read_set(char *input) {
	int i = 0, z = 0;
	for (; input[i] == ' '; i++);//skip spaces to the set
	char set = input[i];//get set
	input = input + i + 2;//skip to numbers
	if ('A' <= set && set <= 'F')//cheack if the set exist
	{
		int i = 0, flag = 0, num;
		Set MySet = malloc(1);//allocation 1 byte
		if (strchr(input, ' ') == NULL) {
			if (strstr(input, "-1") != NULL) {
				if (!(strstr(input, "-1")[2] >= '0' && (strstr(input, "-1")[2] <= '9'))) {
					while (1) {
						if ((input[0] == '-' && input[1] == '1')) {
							break;
						}
						i = 0;
						char buffer[4] = { '\0' };//number
						while (input[i] != ',') {
							if (!(input[i] >= '0' && input[i] <= '9'))//if the char is number
							{
								flag = 1;
								printf("ilegal command.\n");
							}
							buffer[i] = input[i];//input number
							i++;
						}
						if (flag == 1)//flag if find error and not do allocation
							break;
						input = input + i + 1;
						num = atoi(buffer);//change char to int
						if (num == 0)//if the number zero-private situation
							num = -2;
						if (num >= -2 && num <= 127) //cheack the range
						{
							if (strchr(MySet, (char)num) == NULL)//cheack if exit in the array and pointer on the value else null 
							{
								MySet[z++] = (char)num;//enter to the numberto the array as ascii character.example 111=>'o' its save space in the memory
								MySet = realloc(MySet, z + 1);//alloction space for one ascii character
							}
						}
						else {
							printf("ilegal command.\n");
							flag = 1;//error 
							break;
						}
					}
					MySet[z] = '\0';
					if (flag == 0)
						*my_set(set) = MySet;//witch set
				}
				else {
					printf("Ilegal command\n");
				}
			}
			else {
				printf("Missing end of command indicator: '-1'\n");
			}

		}
		else {
			printf("Ilegal command\n");
		}
	}
	else {
		printf("Set dosen't exist.\nEnter letter between A to F.\n");
	}
}
//print the set
void print_set(char *input) {
	int i = 0;
	for (; input[i] == ' '; i++);//skip about the order
	char set = input[i];
	i = 0;
	if ('A' <= set && set <= 'F')//cheack if this set exist
	{
		printf("Set %c: ", set);
		if (*my_set(set) != '\0') {
			for (; i < strlen(*my_set(set)); i++) {
				if (i % 16 == 0 && i > 0)//after 16 numbers we underline
				{
					printf("\n");
				}
				if ((*my_set(set))[i] == (char)-1)//if the number zero-private situation, the charcter -1 is 0,
					printf("0, ");
				else
					printf("%d, ", (*my_set(set))[i]);//print the number in the set
			}
			printf("\n");
		}
		else {
			printf("Empty set.\n");
		}
	}
	else {
		printf("Set dosen't exist.\nEnter letter between A to F.\n");
	}
}
//put all the number of 2 set togather
void union_set(char *input) {
	char set[3] = { '\0' };
	int i = 0, flag = 0;
	for (int j = 0; j < 3; j++) {
		for (; (input[i] == ' ' || input[i] == ','); i++);
		set[j] = input[i];//get  the set for unput
		i++;
	}
	i = 0;
	//if the set correct-we cheak if number from the first set exist in the secound set 
	if (('A' <= set[0] && set[0] <= 'F') && ('A' <= set[1] && set[1] <= 'F')) {
		Set MySet = malloc(1), temp = strcat(*my_set(set[0]), *my_set(set[1]));
		for (int j = 0; j < strlen(temp); j++) {
			if (strchr(MySet, temp[j]) == NULL) {
				MySet[i++] = temp[j];
				MySet = realloc(MySet, i + 1);
			}
		}
		MySet[i] = '\0';
		//if we have third set in the command we get it
		if (('A' <= set[2] && set[2] <= 'F')) {
			*my_set(set[2]) = MySet;
		}
		else {
			if (strlen(MySet) > 0) {
				for (int i = 0; i < strlen(MySet); i++) {
					if (i % 16 == 0 && i > 0){//print 16 numbers in one row
						printf("\n");
					}
					if (MySet[i] == (char)-1)//when we look at the ascii char of -1 as 0  (0 in ascii in null)
						printf("0, ");
					else
						printf("%d, ", MySet[i]);//pint number in the set
				}
				printf("\n");
			}
			else {
				printf("Empty set.\n");
			}
		}

	}
	else {
		printf("Set dosen't exist.\nEnter letter between A to F.\n");
	}
}
//the common numbers of two sets
void intersect_set(char *input) {
	char set[3] = { '\0' };
	int i = 0;
	//get the set from input
	for (int j = 0; j < 3; j++) {
		for (; (input[i] == ' ' || input[i] == ','); i++);
		set[j] = input[i];
		i++;
	}
	i = 0;
	//if the set illegal
	if (('A' <= set[0] && set[0] <= 'F') && ('A' <= set[1] && set[1] <= 'F')) {
		Set MySet = malloc(1);//allcation set
		for (int j = 0; j < strlen(*my_set(set[0])); j++) {
			//if one of the set exit only once and not the other set
			if (strchr(*my_set(set[1]), (*my_set(set[0]))[j]) != NULL && strchr(MySet, (*my_set(set[0]))[j]) == NULL) {
				MySet[i++] = (*my_set(set[0]))[j];
				MySet = realloc(MySet, i + 1);
			}
		}
		MySet[i] = '\0';
		//if have third set in the input
		if (('A' <= set[2] && set[2] <= 'F')) {
			*my_set(set[2]) = MySet;
		}
		else {
			if (strlen(MySet) > 0) //
			{
				for (int i = 0; i < strlen(MySet); i++) {
					if (i % 16 == 0 && i > 0){//print 16 numbers in row
						printf("\n");
					}
					if (MySet[i] == (char)-1)//recognaize -1 as 0(0=>null at  ascii)
						printf("0, ");
					else
						printf("%d, ", MySet[i]);//print character as number
				}
				printf("\n");
			}
			else {
				printf("Empty set.\n");
			}
		}

	}
	else {
		printf("Set dosen't exist.\nEnter letter between A to F.\n");
	}
}
//the numbers that exist in one set but not the other sets
void sub_set(char *input) {
	char set[3] = { '\0' };
	int i = 0;
	//get set for input
	for (int j = 0; j < 3; j++) {
		for (; (input[i] == ' ' || input[i] == ','); i++);
		set[j] = input[i];
		i++;
	}
	i = 0;
	//cheack if the set illgel
	if (('A' <= set[0] && set[0] <= 'F') && ('A' <= set[1] && set[1] <= 'F')) {
		Set MySet = malloc(1);
		//if one of the set exist in one set and not the other set
		for (int j = 0; j < strlen(*my_set(set[0])); j++) {
			if (strchr(*my_set(set[1]), (*my_set(set[0]))[j]) == NULL) {
				MySet[i++] = (*my_set(set[0]))[j];
				MySet = realloc(MySet, i + 1);
			}
		}
		MySet[i] = '\0';
		//if exist third set
		if (('A' <= set[2] && set[2] <= 'F')) {
			*my_set(set[2]) = MySet;
		}
		else {
			if (strlen(MySet) > 0) //if not empty
			{
				for (int i = 0; i < strlen(MySet); i++) {
					if (i % 16 == 0 && i > 0){//print until 16 elements in row
						printf("\n");
					}
					if (MySet[i] == (char)-1)//charcters -1 recognaize as 0 (0 is null in ascii)
						printf("0, ");
					else
						printf("%d, ", MySet[i]);
				}
				printf("\n");
			}
			else {
				printf("Empty set.\n");
			}
		}

	}
	else {
		printf("Set dosen't exist.\nEnter letter between A to F.\n");
	}
}
//the numbers that doesnt exist in the set between the range 0-127
void comp_set(char *input) {
	char set[2] = { '\0' };
	int i = 0;
	//get set from input
	for (int j = 0; j < 2; j++) {
		for (; (input[i] == ' ' || input[i] == ','); i++);
		set[j] = input[i];
		i++;
	}
	i = 0;
	//cheack if the set illgeal 
	if ('A' <= set[0] && set[0] <= 'F') {
		Set MySet = malloc(1);
		for (int j = -1; j <= 127; j++) {
			//if the element not exist in the array
			if (strchr(*my_set(set[0]), (char)j) == NULL) {
				MySet[i++] = (char)j;
				MySet = realloc(MySet, i + 1);
			}
		}
		MySet[i] = '\0';
		//if illegal set get set
		if (('A' <= set[1] && set[1] <= 'F')) {
			*my_set(set[1]) = MySet;
		}
		else {
			if (strlen(MySet) > 0) {//if not empty
				for (int i = 0; i < strlen(MySet); i++) {
					if (i % 16 == 0 && i > 0){//print 16 elements in row
						printf("\n");
					}
					if (MySet[i] == (char)-1)//recognaize -1 as charcters
						printf("0, ");
					else
						printf("%d, ", MySet[i]);//print element of the set
				}
				printf("\n");
			}
			else {
				printf("Empty set.\n");
			}
		}

	}
	else {
		printf("Set dosen't exist.\nEnter letter between A to F.\n");
	}
}