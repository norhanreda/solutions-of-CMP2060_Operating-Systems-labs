#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define max_size 256
 key_t up_queue_key, down_queue_key;
    int up_queue_id, down_queue_id;

struct msgbuff
{
    long mtype;
    char mtext[max_size];
};



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

    pid_t process_id = getpid();
    struct msgbuff msgbuff_send;
    struct msgbuff msgbuff_recv;
    msgbuff_send.mtype = process_id % 10000;
    printf("i'm a client  my PID=%d ,sending message type = %ld \n",process_id, msgbuff_send.mtype);
    //.//////////////client process///////////////

    while (1)
    {

        //gets the message from consle

        printf("pleasae enter the message with max length 256 \n");
        fgets(msgbuff_send.mtext,max_size, stdin);
        //gets(msgbuff_send.mtext);
        
       
        int send=msgsnd(up_queue_id,&msgbuff_send,sizeof(msgbuff_send.mtext),!IPC_NOWAIT);
        if(send==-1)
          {
              printf("error in sending from client to server \n");
          }
          else
          {
                 printf("i'm the client i sent: %s to server ",msgbuff_send.mtext);
                 //printf("rsize of message %ld \n" ,sizeof(msgbuff_send.mtext));
               int recv=msgrcv(down_queue_id,&msgbuff_send,sizeof(msgbuff_send.mtext),msgbuff_send.mtype,!IPC_NOWAIT);
               if(recv==-1)
               {
                   printf("error in receving from server \n");
               }
               else
               {
                   printf("i'm the client i received: %s from server \n ",msgbuff_send.mtext);

               }

          }

    }

    return 0;
}