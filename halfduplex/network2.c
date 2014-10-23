#include"networkhdr.h"
#define MYPORT 4950
#define DESTPORT 3000
#define DATA_SIZE 1000
#include"sender.c"
#include"receiver.c"
int main(int argc,char *argv[])
{
	printf("WELCOME TO TILOCHAT...\nTRANSMITION PORT:%d\n",DESTPORT);
	printf("RECEPTION PORT:%d\n",MYPORT);
	while(1){
		if(argc !=2)
			printf("invalid IP\n");
		int status;
		
		if((status = sender(argv[1])) !=0){
				printf("error in sending\n");
		}
		else {
			if((status = receiver())!=0)
				printf("receiving error\n");
		}
	}
		return 0;
}
