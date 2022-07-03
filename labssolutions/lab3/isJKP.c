#include<stdio.h>
#include<string.h>
#include <ctype.h>
int isJKP(char *kangaroo , char *joey,int lk,int lj)
{
    
    if(lj==0) 
       return 1;

    if(lk==0)
       return 0;

    if(tolower(kangaroo[lk-1])==tolower(joey[lj-1])) 
       return isJKP(kangaroo,joey,lk-1,lj-1); 
    
    else
       return isJKP(kangaroo,joey,lk-1,lj);


}

int main(int argc, char **argv)
{
  
    if(argc < 3)
       printf("please enter all values !");
    else
    {

     int lk=strlen(argv[1]);
     int lj=strlen(argv[2]);

          if(lk>lj)
           {
                 if(isJKP(argv[1],argv[2],lk,lj)==1)
                       printf("1");
                 else
                       printf("0");

           }
           else if(lk<lj)
           {
               if(isJKP(argv[2],argv[1],lj,lk)==1)
                   printf("1");
               else
                   printf("0");

           }
           else
           {
             printf("0");

           }

    }




    return 0;
}