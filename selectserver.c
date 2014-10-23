#include"networkhdr.h"
#define PORT 9034
int main()
{
	fd_set master;
	fd_set read_fds;
	struct sockaddr_in myaddr;
	struct sockaddr_in remoteaddr;
	int fdmax;
	int listener;
	int newfd;
	char buf[256];
	int nbytes;
	int yes=1;
	int addrlen;
	int i,j;

	FD_ZERO(&master);
	FD_ZERO(&read_fds);

	if((listener = socket(AF_INET, SOCK_STREAM,0))== -1){
		perror("socket");
		exit(1);
	}

	if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))==-1){
		perror("setsockopt");
		exit(1);
	}

	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = INADDR_ANY;
	myaddr.sin_port = htons(PORT);
	memset(&(myaddr.sin_zero),'\0',8);
	if(bind(listener,(struct sockaddr *)&myaddr,sizeof(myaddr)) == -1){
		perror("bind");
		exit(1);
	}

	if(listen(listener,10)==-1){
		perror("listen");
		exit(1);
	}

	FD_SET(listener, &master);

	fdmax = listener;

	for(;;){
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL,NULL,NULL)== -1){
			perror("select");
			exit(1);
		}
		for(i=0; i<=fdmax; i++){
			if(FD_ISSET(i, &read_fds)){
				if(i == listener){
					addrlen = sizeof(remoteaddr);
					if((newfd = accept(listener,(struct sockaddr *)&remoteaddr,&addrlen))== -1){
						perror("accept");
					}else{
						FD_SET(newfd,&master);
						if(newfd > fdmax){
							fdmax = newfd;
						}
						printf("selectserver: new connection from %s on socket %d\n", inet_ntoa(remoteaddr.sin_addr),newfd);
					}
				}else{
					if((nbytes = recv(i,buf,sizeof(buf), 0))<=0){
						if(nbytes == 0){
							printf("selectserver:socket %d hung up\n",i);
						}else{
							perror("recv");
						}
						close(i);
						FD_CLR(i, &master);
					}else{
						for(j=0;j<=fdmax;j++){
							if(FD_ISSET(j,&master)){
								if(j!=listener && j!=i){
									if(send(j,buf,nbytes,0)== -1){
										perror("send");
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

