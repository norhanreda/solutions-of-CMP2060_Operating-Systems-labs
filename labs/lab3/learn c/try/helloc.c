#include <stdio.h>
int main()
{
	
Char name[50];
name[0] = 'D';
name[1] = 'a';
name[2] = 'v';
name[3] = 'e';
name[4] = '\0';
char * p = &name[0];
printf("The name is %s \n", p);

    return 0;
} 
