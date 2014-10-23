#include"networkhdr.h"
#define MYPORT 4950//listening to this port
#define DESTPORT//client's or destination port used when server sends
#define DATA_SIZE 10000
int main(int argc,char *argv[])
{
	int sfd;
	struct sockaddr_in myaddr;//here use '127.0.0.1'
	struct sockaddr_in destaddr;//same machine addr
	int addrlen, numbytes;
	char buf[DATA_SIZE];

	if((sfd = socket(AF_INET, SOCK_DGRAM, 0))== -1){
		perror("socket:");
		exit(1);
	}

	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(MYPORT);
	myaddr.sin_addr.s_addr =INADDR_ANY; //inet_addr(IPADDR);
	memset(&(myaddr.sin_zero),'\0',8);

	if(bind(sfd,(struct sockaddr *)&myaddr, sizeof(struct sockaddr))== -1){
		perror("bind:");
		exit(1);
	}

	addrlen = sizeof(struct sockaddr);
	if((numbytes = recvfrom(sfd,buf,DATA_SIZE-1,0,(struct sockaddr *)&destaddr, &addrlen))== -1){
		perror("recvfrom:");
		exit(1);
	}
	printf("got packet from %s\n", inet_ntoa(destaddr.sin_addr));
	printf("packet is %d bytes long\n",numbytes);
	buf[numbytes] = '\0';
	printf("packet contains  \"%s\"  \n",buf);
	close(sfd);

	return 0;
}
