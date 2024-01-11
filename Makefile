																																						
server: server.o 
	gcc -o server server.o  
	
server.o :server.c  
	gcc -o server.o -c server.c 
	
client: client.o 
	gcc -o client client.o  
	
client.o :server.c  
	gcc -o client.o -c client.c

serv: server
clnt: client
clean:
	rm -rf *.o server client
