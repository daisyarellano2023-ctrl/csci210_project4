
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

struct message {
	char source[50];
	char target[50]; 
	char msg[200]; // message body
};

void terminate(int sig) {
	printf("Exiting....\n");
	fflush(stdout);
	exit(0);
}

int main() {
	int server;
	int target;
	int dummyfd;
	struct message req;
	signal(SIGPIPE,SIG_IGN);
	signal(SIGINT,terminate);
	server = open("serverFIFO",O_RDONLY);
	dummyfd = open("serverFIFO",O_WRONLY);

	while (1) {
		// TODO:
		// read requests from serverFIFO
		// so i should open the file in read 
		ssize_t count = read(server,&req,sizeof(struct message));

		
		if(count==0){
			continue;
		}
		else if (count==-1)
		{
			perror("ERROR reading request");
		}
		else if (count>0)
		{
			printf("Received a request from %s to send the message %s to %s.\n",req.source,req.msg,req.target);

		}
		
		

		// open the target 
	
		target = open(req.target,O_WRONLY);

		if (target==-1){
			
			perror("ERROR opening");
		}


		if(target>=0){

			write(target,&req,sizeof(req));

		}
		close(target);

		// TODO:
		// open target FIFO and write the whole message struct to the target FIFO
		// close target FIFO after writing the message




	}
	close(server);
	close(dummyfd);
	return 0;
}

