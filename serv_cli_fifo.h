#ifndef SERV_CLI_FIFO_H_INCLUDED
#define SERV_CLI_FIFO_H_INCLUDED



#define NMAX 20
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"


struct ClientQuestion {
    int client_pid;
    int a;
    int b;
};


struct ServerResponse {
    int client_id ;
    int server_id;
    int result;
};


#endif
