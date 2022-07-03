#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
void handler(int signum);
int ch1,ch2,search_element;
int main(int argc, char **argv)
{
  

  if (argc < 2)
    printf("%s", "invalid arguments ! \n");
  else
  {

    search_element = (atoi)(argv[1]);
    int arr_size = argc - 2;
    //printf("%d \n", search_element);
    int arr[arr_size];
    for (int i = 0; i < arr_size; i++)
    {
      arr[i] = (atoi)(argv[i + 2]);
    }

    /*for(int i=0;i<arr_size;i++)
{
printf("%d \t ",arr[i]);

}*/
    int half_index = arr_size / 2;

    int child_index = 0;
    int pid1, pid2;
 
    signal(SIGUSR1, handler); // so  the handdler is defined for parent and his childrens
     printf("%s %d \n", "I am the parent, PID = ", getpid());
    ch1 = fork();

    if (ch1 == -1)
      printf("Error in forking !");

    else if (ch1 == 0) //childern codes
    {

      
        printf("%s %d %s %d \n", "I am the first child, PID =  ", getpid(), ", PPID =  ", getppid());
        int found1 = 0;
        int flag1=0;
        for (int i = 0; i < half_index; i++)
        {
          if (arr[i] == search_element)
          {
            found1 = i;
            flag1=1;
          }
        }
        if (flag1 != 0)
        {
          kill(getppid(), SIGUSR1);
          exit(found1);
        }
        else
        {
          sleep(3);
          //printf("%s %d %s %d \n", "I am the first child termenating, PID =  ", getpid(), ", PPID =  ", getppid());
          printf(" Child 1  terminates \n ");
          exit(0);
        }
      
      
    }

    else
    {

      ch2 = fork();
      if (ch2 == -1)
        printf("Error in forking !");
      else if (ch2 == 0) //child 2 code
      {
      
        printf("%s %d %s %d \n", "I am the second child, PID =  ", getpid(), ", PPID =  ", getppid());

        int found2 = 0;
        int flag2=0;
        for (int i = half_index; i < arr_size; i++)
        {
          if (arr[i] == search_element)
          {
            found2 = i;
            flag2=1;
          }
        }
        if (flag2 != 0)
        {
          kill(getppid(), SIGUSR1);
          exit(found2);
        }
        else
        {
          sleep(3);
          //printf("%s %d %s %d \n", "I am the second child termenating, PID =  ", getpid(), ", PPID =  ", getppid());
          printf(" Child 2  terminates \n");
          exit(0);
        }
      

      }
      else //parent code
      {
   int pid1,pid2,stat_loc1,stat_loc2;
        //printf("%s %d \n", "I am the parent, PID = ", getpid());
        sleep(5);
   
      pid1=wait(&stat_loc1);
      pid2=wait(&stat_loc2);
      /*printf("\nA child with PID=%d terminated\n\n", pid1);
      printf("\nA child with PID=%d terminated\n\n", pid2);*/

        printf("%s \n", "Value Not Found");
       
       exit(0);
        /*4.	It forks two children in parallel and then sleeps for 5 seconds. 
5.	It waits for both children to exit before it can terminate.
6.	Before termination, it prints “Value Not Found”. */
      }
    }
  }

  return 0;
}

void handler(int signum)
{
    int stat_loc,pidh,child;

    pidh=wait(&stat_loc);
    
    if(pidh==ch1)
     child=1;
     else if(pidh==ch2)
     child=2;

     if(!(stat_loc & 0x00FF))
      {
         printf("%s %d %s %d %s %d \n","a child ",child,"has found the element:",search_element,"at location:",stat_loc>>8);
        killpg(getpgrp(),SIGKILL);

      }



  signal(SIGUSR1, handler); // so  it use it again instead of default 
}


        /*
          a- Who will be the process executing the code in the handler? 
            The Parent.
            How did you know? 
            The handler should be called whenever SIGUSR1 is called ,so when the child sends the signal
            the parent should capture and process it whenever it was sent. 
        */

       /*
        b - Why is it not possible that the signal handler may not receive an exit code? 
              When a process terminates using a signal it must send an exit code by default to indicate if
         the process terminated normally or not. You can customize exit codes to indicates special cases or to communicate with parent
        */

