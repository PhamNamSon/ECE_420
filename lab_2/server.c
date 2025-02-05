#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "common.h"
#include "timer.h"

char **theArray;
pthread_mutex_t *arrayLocks;


void *ServerEcho(void *args)
{
    int clientFileDescriptor=(long)args;
    ClientRequest rqst;
    char buffer[COM_BUFF_SIZE];
    read(clientFileDescriptor, buffer, COM_BUFF_SIZE);
    ParseMsg(buffer, &rqst);
    printf("reading from client:%s\n",buffer);
    pthread_mutex_lock(&arrayLocks[rqst.pos]);
    if (rqst.is_read){
        getContent(buffer, rqst.pos, theArray);
    } else {
        setContent(rqst.msg, rqst.pos, theArray);
        getContent(buffer, rqst.pos, theArray);
    }
    pthread_mutex_unlock(&arrayLocks[rqst.pos]);
    write(clientFileDescriptor,buffer,COM_BUFF_SIZE);
    close(clientFileDescriptor);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "usage: %s <Size of theArray_ on server> <server ip> <server port>\n", argv[0]);
        exit(0);
    }
    int n = atoi(argv[1]);
    char *server_ip = argv[2];
    int server_port = atoi(argv[3]);

    theArray = (char **)malloc(n * sizeof(char *));
    arrayLocks = malloc(n * sizeof(pthread_mutex_t));
    for (int i = 0; i < n; i++)
    {
        theArray[i] = (char *)malloc(COM_BUFF_SIZE * sizeof(char));
        snprintf(theArray[i], COM_BUFF_SIZE, "String[%d]: initial value", i);
        pthread_mutex_init(&arrayLocks[i], NULL);
    }

    int serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    int clientFileDescriptor;
    struct sockaddr_in sock_var;
    sock_var.sin_addr.s_addr = inet_addr(server_ip);
    sock_var.sin_port = server_port;
    sock_var.sin_family = AF_INET;
    int i;
    pthread_t t[COM_NUM_REQUEST];
    if (bind(serverFileDescriptor, (struct sockaddr *)&sock_var, sizeof(sock_var)) >= 0)
    {
        printf("socket has been created\n");
        listen(serverFileDescriptor, 2000);
        while (1) // loop infinity
        {
            for (i = 0; i < COM_NUM_REQUEST; i++) 
            {
                clientFileDescriptor = accept(serverFileDescriptor, NULL, NULL);
                printf("Connected to client %d\n", clientFileDescriptor);
                pthread_create(&t[i], NULL, ServerEcho, (void *)(long)clientFileDescriptor);
                pthread_join(t[i], NULL);
            }
        }
        close(serverFileDescriptor);
    }
    else
    {
        printf("socket creation failed\n");
    }
    for (int i = 0; i < n; i++) {
        free(theArray[i]);
        pthread_mutex_destroy(&arrayLocks[i]);
    }
    free(theArray);
    free(arrayLocks);
    return 0;
}