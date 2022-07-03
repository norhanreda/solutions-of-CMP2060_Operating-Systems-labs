#include <stdio.h>

void  waitforInput()
{
	char  XX;
	printf("print any Charachter followed by enter to continue ...");
        scanf("%c",&XX);
        printf("\n");
}

int main(int argc, char *argv[])
{
    
    
    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };
    char *test = "abcd";
    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    
    printf("Size of integer is %ld \n. The total size of array of ages is : %ld \nTherefore the total number of elements in the array is: %d\n", sizeof(int), sizeof(ages),count);
    
   
    waitforInput();
    int i = 0;

    // first way using indexing
    for(i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }

    waitforInput();
    printf("---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;
    char *tt =test;
    // second way using pointers
    for(i = 0; i < count; i++) {
        printf("%s is %d years old with char %c , %p %p %p.\n",
                *(cur_name+i), *(cur_age+i), *(tt+i), (cur_name+i),(cur_age+i),(tt+i));
    }

    printf("---\n");
    waitforInput();
    printf("---\n");
    printf("Take Care Size of cur_age is %ld while size of ages is %ld \n",sizeof(cur_age),sizeof(ages)); 

    waitforInput();
    // third way, pointers are just arrays
    for(i = 0; i < count; i++) {
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // fourth way with pointers in a stupid complex way
    for(cur_name = names, cur_age = ages;
            (cur_age - ages) < count;
            cur_name++, cur_age++)
    {
        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }

    return 0;
}
