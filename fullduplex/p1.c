#include"networkhdr.h"
#define PORT 4970
#define DESTPORT 3500 
#define DATA_SIZE 1000
int main(int argc, char *argv[])
{
	if(argc !=2){
		printf("usage error:expecting valid IP address\n");
		exit(1);
	}
	printf("welcome to ....TILOCHAT....\n");
	printf("reception port:%d\ntransmition port:%d\n",PORT,DESTPORT);
	fd_set master;
	fd_set read_fds;
	struct sockaddr_in myaddr;
	struct sockaddr_in destaddr;
	int fdmax;
	int listener;
	char buf[DATA_SIZE];
	int nbytes;
	int addrlen= sizeof(struct sockaddr);
	int i,j;

	FD_ZERO(&master);
	FD_ZERO(&read_fds);

	if((listener = socket(AF_INET, SOCK_DGRAM,0))== -1){
		perror("socket");
		exit(1);
	}
	destaddr.sin_family = AF_INET;
	destaddr.sin_addr.s_addr = inet_addr(argv[1]);
	destaddr.sin_port = htons(DESTPORT);

	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = INADDR_ANY;
	myaddr.sin_port = htons(PORT);
	memset(&(myaddr.sin_zero),'\0',8);
	if(bind(listener,(struct sockaddr *)&myaddr,sizeof(struct sockaddr)) == -1){
		perror("bind");
		exit(1);
	}

	FD_SET(0,&master);

	FD_SET(listener, &master);

	fdmax = listener;

	for(;;){
		for(j=0;j<DATA_SIZE;j++){
			buf[j]=0;
		}
		read_fds = master;
		if(i=select(fdmax+1, &read_fds, NULL,NULL,NULL)== -1){
			perror("select");
			exit(1);
		}
		if(FD_ISSET(0,&read_fds)){

			printf("SENT\n\n");
			gets(buf);

			if((nbytes=sendto(listener,buf,strlen(buf),0,(struct sockaddr *)&destaddr,addrlen))==-1){
				perror("sendto");
				exit(1);
			}
		}
		else if(FD_ISSET(listener,&read_fds)){
			if((nbytes = recvfrom(listener,buf,sizeof(buf)-1,0,(struct sockaddr *)&destaddr,&addrlen))==-1){
					perror("recv");
					exit(1);
					}
						printf("RECVD:%s\n\n",buf);

		}else
			printf("UNDEFINED BHVR\n");
	}
	return 0;
}

