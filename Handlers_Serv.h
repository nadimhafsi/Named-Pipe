#ifndef HANDLERS_SERV_H_INCLUDED
#define HANDLERS_SERV_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Handler for waking up the server after receiving the SIGUSR1 signal
void hand_reveil(int sig) {
   printf("SIGUSR1 signal received, server wake-up...\n");

}

// Handler for terminating the server when any signal is received
void end_server(int sig) {

     printf("end of program...\n");
    exit(0);
}

#endif // HANDLERS_SERV_H_INCLUDED
