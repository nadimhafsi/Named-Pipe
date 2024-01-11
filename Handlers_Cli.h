#ifndef HANDLERS_CLI_H_INCLUDED
#define HANDLERS_CLI_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void hand_reveil(int sig) {

   printf("SIGUSR1 signal received. client wakes up......\n");

}

#endif // HANDLERS_CLI_H_INCLUDED
