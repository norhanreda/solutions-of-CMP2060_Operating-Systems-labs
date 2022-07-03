#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include<signal.h>
#define max_size 256
int shmid;
int sem1; //
int sem2;// 
int sem3;
union Semun semun1;
union Semun semun2;
union Semun semun3;
//union Semun sem1,sem2;

/* arg for semctl system calls. */
union Semun
{
    int val;               /* value for SETVAL */
    struct semid_ds *buf;  /* buffer for IPC_STAT & IPC_SET */
    ushort *array;         /* array for GETALL & SETALL */
    struct seminfo *__buf; /* buffer for IPC_INFO */
    void *__pad;
};

void down(int sem)
{
    struct sembuf p_op;

    p_op.sem_num = 0;
    p_op.sem_op = -1;
    p_op.sem_flg = !IPC_NOWAIT;

    if (semop(sem, &p_op, 1) == -1)
    {
        perror("Error in down()");
        exit(-1);
    }
}

void up(int sem)
{
    struct sembuf v_op;

    v_op.sem_num = 0;
    v_op.sem_op = 1;
    v_op.sem_flg = !IPC_NOWAIT;

    if (semop(sem, &v_op, 1) == -1)
    {
        perror("Error in up()");
        exit(-1);
    }
}


/* reverse a message */
void reverse(char* msg, char* reversed) {
int i;
for (i=0; i<strlen(msg); ++i)
reversed[i] = msg[strlen(msg) - i - 1];
}

void handler(int signum)
{
printf("server is terminated \n");
shmctl(shmid, IPC_RMID, (struct shmid_ds *)0);
semctl(sem1, 0, IPC_RMID, semun1);
semctl(sem2, 0, IPC_RMID, semun2);
semctl(sem3, 0, IPC_RMID, semun3);
printf("free shared memory and distroy semaphores ! \n");
signal(SIGINT,handler);
exit(0);
}



int main()
{
    

  
shmid = shmget(65,max_size*sizeof(char), IPC_CREAT | 0664);
     sem1 = semget(66, 1, 0666 | IPC_CREAT);
     sem2 = semget(67, 1, 0666 | IPC_CREAT);
     sem3 = semget(68, 1, 0666 | IPC_CREAT);
if (shmid == -1 || sem1==-1 || sem2==-1 || sem3==-1)
    {
        perror("Error in create \n");
        exit(-1);
    }
    printf("\n server Shared memory ID = %d\n", shmid);

    semun1.val = 0; /* initial value of the semaphore, Binary semaphore */
    semun2.val=0;
    semun3.val=1;
    if (semctl(sem1, 0, SETVAL, semun1) == -1 || semctl(sem2, 0, SETVAL, semun2) == -1 || semctl(sem3, 0, SETVAL, semun3) == -1)
    {
        perror("Error in semctl \n");
        exit(-1);
    }
    
    void *shmaddr = shmat(shmid, (void *)0, 0);
    if (*(int*)shmaddr == -1)
    {
        perror("Error in client to attach to memory \n");
        exit(-1);
    }
      
      ////////////////process of server/////////////////
      signal(SIGINT,handler);
      while(1)
      {
           
       
           down(sem1);

           printf("i'm the server I read a message: %s from the shared memory \n",(char *)shmaddr);
           char *s=(char*) malloc(max_size);
           strcpy(s,(char *)shmaddr);
            //printf(s);
           reverse(s,(char *)shmaddr);
        
            
           printf("i'm the server I write message: %s in the shared memory \n",(char *)shmaddr);
            up(sem2);




      }
  






    return 0;
}