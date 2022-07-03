#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char **argv)
{

    if (argc < 4)
        printf("invalid arguments !, please enter all arguments \n");

    else
    {
        char *gradesfile=argv[1];
        int TAscount = atoi(argv[2]);
        int passgrade = atoi(argv[3]);
        int studentscount = 0;
        int *grades;

        /* printf("%s",gradesfile);
  printf("\n");

  printf("%d",TAscount);
  printf("\n");

  printf("%d",passgrade);
  printf("\n");*/
        //read from file
        FILE *fptr;
        fptr = fopen(gradesfile, "r");

        if (fptr == NULL)
        {
            printf("Error: can't open the file ");
            exit(1);
        }
        else
        {

            char data[10];
            if (fgets(data, 10, fptr) != NULL)
                studentscount = atoi(data);

            //printf("%d %s", studentscount, "\n");
            int grades[studentscount];
            int index = 0;
            int midtermgrade[studentscount];
            int finalgrade[studentscount];
            while (fgets(data, 10, fptr) != NULL && index < studentscount)
            {
                sscanf(data, "%d %d", &midtermgrade[index], &finalgrade[index]);
                // printf("%d %d %d %s",midtermgrade,finalgrade,grades[index],"\n");

                index++;
            }
            fclose(fptr);

            int stat_loc, ti, i;
            int pid;
            int groupscount = studentscount / TAscount;
            //printf("%d   ",groupscount);
            int finalcount[TAscount];
            int PIDS[TAscount]; //to store the pid of each TA

            for (ti = 0; ti < TAscount; ti++) // forking TAs
            {
                pid = fork();

                if (pid == -1)
                    perror("Error: in forking !");

                //////TAs code////////
                else if (pid == 0) //TAs code
                {

                    int passedcount = 0;
                    int firstindex = ti * groupscount;
                    int lastindex;
                    if (ti != TAscount - 1)
                    {
                        lastindex = firstindex + groupscount - 1;
                    }
                    else
                        lastindex = studentscount - 1;

                    for (i = firstindex; i <= lastindex; i++)
                    {
                        grades[i] = midtermgrade[i] + finalgrade[i];
                        if (grades[i] >= passgrade)
                            passedcount++;
                    }
                    // printf("%d   ",passedcount);
                    exit(passedcount); //child is terminated 
                }

                ////////////department committee//////////
                else
                {
                    //PIDS[ti] = pid;
              
                 waitpid(pid, &stat_loc, 0); // department wait for all TAs to finish

                if (!(stat_loc & 0x00FF))
                {

                    finalcount[ti] = stat_loc >> 8; // retuen the final count in the form of exit code
                    
                }
                else
                    finalcount[ti] = 0;
            


                //printf("%d \n", finalcount[ti]); // why printing here causes problem ?
                    
                }
            }

           
            ///////////

            for (i = 0; i < TAscount; i++)
            {

                printf("%d ", finalcount[i]);
            }

            printf("\n");

            /////////////////////////////////////////////
        }
    }

    return 0;
}