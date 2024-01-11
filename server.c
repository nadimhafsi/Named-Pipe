#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(){
/*Declarations */
int fd_fifo1,fd_fifo2;
int b;

struct ClientQuestion client;
struct ServerResponse response;

/* named pipe creation*/

    unlink(FIFO1);
    unlink(FIFO2);

if (mkfifo(FIFO1,0666) <0 || mkfifo(FIFO2,0666) <0  ){
       perror("error in creation of named tube\n");
       exit(1);
}


/* Introduction */
printf("***********************************************\n");
printf("************ SERVER APPLICATION ***************\n");
printf("***********************************************\n");
printf("This server application listens for client requests\n");
printf("via named pipes and performs simple arithmetic\n");
printf("operations on the received data.\n");
printf("The server communicates with clients using two named pipes:\n");
printf("   - %s (for receiving client questions)\n", FIFO1);
printf("   - %s (for sending server responses)\n", FIFO2);
printf("When a client sends a question, the server calculates\n");
printf("the result and responds to the client. The server and\n");
printf("client synchronize their actions using signals 'SIGUSR1' (\n");
printf("Press Ctrl+C to exit the server.\n");
printf("***********************************************\n\n");


/* named pipe opening*/
fd_fifo1=open(FIFO1,O_RDONLY);
fd_fifo2=open(FIFO2,O_WRONLY);

 if (fd_fifo1 == -1 || fd_fifo2 ==-1) {
        perror("Error opening file.\n");
        exit(1);
  }
  


/* Handler installation */
for (int i = 1; i < NSIG; i++) {
    signal(i, end_server);
}
signal(SIGUSR1, hand_reveil);


while(1){
/* reading a question*/
sleep(1);
if ((b=read(fd_fifo1,&client,sizeof(struct ClientQuestion)))<0)
{
   perror("error in reading the question. \n");
   close(fd_fifo1);
   exit(1);
}
else if(b>0) {
printf(ANSI_COLOR_GREEN"integer_1=%d\n"ANSI_COLOR_RESET,client.a);
printf(ANSI_COLOR_GREEN"integer_2=%d\n"ANSI_COLOR_RESET,client.b);



/* building the response */
response.server_id=getpid();
response.client_id=client.client_pid;
response.result=client.a + client.b;

/* send response*/


write(fd_fifo2,&response,sizeof(struct ServerResponse));

/* SIGUSR1 signal sent to the client concerned */
kill(response.client_id, SIGUSR1);


printf("pause server...\n");
pause();

printf("server continue...\n");
}
}

    close(fd_fifo1);
    close(fd_fifo2);

    return 0;
}
