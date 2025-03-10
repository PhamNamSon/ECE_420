#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include "common.h"
#include "timer.h"

char **theArray;
pthread_mutex_t *mutex;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s <Size of theArray_ on server> <server ip> <server port>\n", argv[0]);
        exit(0);
    }
    int n = atoi(argv[1]);
    char *server_ip = argv[2];
    int server_port = atoi(argv[3]);

    theArray = (char **)malloc(n * sizeof(char *));
    mutex = (pthread_mutex_t *)malloc(n * sizeof(pthread_mutex_t));
    for (int i = 0; i < n; i++) {
        theArray[i] = (char *)malloc(COM_BUFF_SIZE * sizeof(char));
        snprintf(theArray[i], COM_BUFF_SIZE, "String[%d]: initial value", i);
        pthread_mutex_init(&mutex[i], NULL);
    }

    int serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    int clientFileDescriptor;
    struct sockaddr_in sock_var;
    sock_var.sin_addr.s_addr = inet_addr(server_ip);
    sock_var.sin_port = server_port;
    sock_var.sin_family = AF_INET;

    
}