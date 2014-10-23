//#define DESTPORT 4950//3000//client's or destination port used when server sends
//#define DATA_SIZE 10000
int sender(char *s)
{
	printf("\n\nSEND MESSEGE:enter text\n");
	int sfd;
	struct sockaddr_in destaddr;//same machine addr
	int addrlen,i, numbytes;
	char msg[DATA_SIZE];
	//read messege from screen
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
	destaddr.sin_addr.s_addr = inet_addr(s);
	memset(&(destaddr.sin_zero),'\0',8);

	addrlen = sizeof(struct sockaddr);
	if((numbytes = sendto(sfd,msg,strlen(msg),0,(struct sockaddr *)&destaddr, addrlen))== -1){
		perror("sendto:");
		exit(1);
	}
	printf("sent  %d bytes to %s\n",numbytes,inet_ntoa(destaddr.sin_addr));
	close(sfd);
	return 0;
}
