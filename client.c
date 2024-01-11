#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(){
/* Déclarations */
int fd_fifo1,fd_fifo2;
int a;

struct ClientQuestion client;
struct ServerResponse response;


/* named pipe opening*/




fd_fifo1=open(FIFO1,O_WRONLY);
fd_fifo2=open(FIFO2,O_RDONLY);

/* Handler installation */

signal(SIGUSR1, hand_reveil);


/* Building and sending a question */
client.client_pid=getpid();


printf("Enter an integer: ");
scanf("%d", &client.a);

printf("Enter another integer: ");
scanf("%d", &client.b);


if(( a=write(fd_fifo1,&client,sizeof(struct ClientQuestion)))<0)
{

perror("Error sending. \n");
close(fd_fifo1);
exit(1);
}
else if(a>1)
printf("question sent\n");


/* Attente de la réponse */



printf("pause client...\n");
pause();

printf("client continue...\n");



/* Reading */

read(fd_fifo2,&response,sizeof(struct ServerResponse));




/* Sends SIGUSR1 signal to server  */
kill(response.server_id, SIGUSR1);


printf("pid=%d\n",response.client_id);
printf(ANSI_COLOR_RED"result=%d\n"ANSI_COLOR_RESET,response.result);


close(fd_fifo1);
close(fd_fifo2);



}
