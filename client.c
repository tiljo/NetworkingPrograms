#include"networkhdr.h"
//#define MYPORT 3000//listening to this port
#define DESTPORT 3490 
//#define IPADDR "192.168.1.5"
//#define IPADDR "127.0.0.1"
#define DATA_SIZE 10000
int main(int argc,char *argv[])
{
	if(argc !=2){
		printf("usage error: invalid IP address\n");
		exit(1);
	}
	int sfd;
	//struct sockaddr_in myaddr;//here use '127.0.0.1'
	struct sockaddr_in destaddr;//same machine addr
	int addrlen,i, numbytes;
//	char buf[DATA];
	char msg[DATA_SIZE];
	for(i=0;i<DATA_SIZE;i++){
		scanf("%c",&msg[i]);
		if(msg[i]==EOF || msg[i]=='\n')
			break;
	}
	msg[i]=0;

	if((sfd = socket(AF_INET, SOCK_DGRAM, 0))== -1){
		perror("socket:");
		exit(1);
	}

	destaddr.sin_family = AF_INET;
	destaddr.sin_port = htons(DESTPORT);
	destaddr.sin_addr.s_addr = inet_addr(argv[1]);
	memset(&(destaddr.sin_zero),'\0',8);

/*	if(bind(sfd,(struct sockaddr *)&myaddr, sizeof(struct sockaddr))== -1){
		perror("bind:");
		exit(1);
	}*/

	addrlen = sizeof(struct sockaddr);
	if((numbytes = sendto(sfd,msg,strlen(msg),0,(struct sockaddr *)&destaddr, addrlen))== -1){
		perror("sendto:");
		exit(1);
	}
	//printf("sent packet from %s\n", inet_ntoa(destaddr.sin_addr));
	printf("sent  %d bytes to %s\n",numbytes,inet_ntoa(destaddr.sin_addr));
	//buf[numbytes] = '\0';
	//printf("packet contains \ "%s \" \n",buf);
	close(sfd);
	return 0;
}
