//NOY DAGAN AND ALINE KARID
#include "set.h"

void main() {
	char *raw_input;
	printf(">>>");//prompt
	raw_input = get_input();//enter command
	while (strstr(raw_input, ":halt") == NULL)//stop when  :halt exist
	{
		input_decoder(raw_input);//the order
		free(raw_input);//free array 
		printf(">>>");//prompt
		raw_input = get_input();//enter command
	}
}