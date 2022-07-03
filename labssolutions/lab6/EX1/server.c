#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include<signal.h>
#define max_size 256
 key_t up_queue_key, down_queue_key;
int up_queue_id, down_queue_id;
   


struct msgbuff
{
    long mtype;
    char mtext[max_size];
};

/* reverse a message */
void reverse(char* msg, char* reversed) {
int i;
for (i=0; i<strlen(msg); ++i)
reversed[i] = msg[strlen(msg) - i - 1];
}

void handler(int signum)
{
   printf("server is terminated \n");
   msgctl(up_queue_id,IPC_RMID,(struct msqid_ds *)0);
   msgctl(down_queue_id,IPC_RMID,(struct msqid_ds *)0);
   printf("up and down queues are removed ! \n");
   exit(0);

}

int main()
{


    //create unique keys for msg queues //
    up_queue_key = ftok("up", 65);
    down_queue_key = ftok("down", 65);

    //get the queues ids //
    up_queue_id = msgget(up_queue_key, 0666 | IPC_CREAT);
    down_queue_id = msgget(down_queue_key, 0666 | IPC_CREAT);

    if (up_queue_id == -1 || down_queue_id == -1)
    {
        printf("error in creation \n");
        exit(-1);
    }


    printf("up queue is created with up_id=%d  , down queue is created with down_id= %d \n", up_queue_id, down_queue_id);

    
    struct msgbuff msgbuff_send;
    struct msgbuff msgbuff_recv;
   
    
    //.//////////////server process///////////////
   signal(SIGINT,handler);
    
    while (1)
    {

        

        //receive the message 
       int recv=msgrcv(up_queue_id,&msgbuff_recv,sizeof(msgbuff_recv.mtext),0,!IPC_NOWAIT);
        if(recv==-1)
          {
              printf("error in receving from client to server \n");
          }
          else
          {
                 
                   memset(msgbuff_send.mtext,0,max_size);
                 reverse(msgbuff_recv.mtext,msgbuff_send.mtext);
                 memset(msgbuff_recv.mtext,0,max_size);
            
                  strcpy(msgbuff_recv.mtext,msgbuff_send.mtext);
                 printf("reversed message %s \n" ,msgbuff_send.mtext);

                int send = msgsnd(down_queue_id, &msgbuff_recv, sizeof(msgbuff_recv.mtext), !IPC_NOWAIT);
               if(send== -1)
               {
                   printf("error in sending from server \n");
               }
               else
               {
                   printf("finish reversing all is well \n");

               }

          }

    }

    return 0;
}