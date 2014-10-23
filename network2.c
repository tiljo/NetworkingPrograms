#include"networkhdr.h"
#define MYPORT 4950
#define DESTPORT 3000 
#define DATA_SIZE 1000
#include"sender.c"
#include"receiver.c"
int main(int argc,char *argv[])
{
	printf("WELCOME TO TILOCHAT...\nRECEPTION PORT:%d\n",MYPORT);
	printf("TRANSMITION PORT:%d\n",DESTPORT);
	

	while(1){
		if(argc !=2)
			printf("invalid IP\n");
		int status;
		if((status = receiver()) !=0){
			printf("error in receiving\n");
		}else{
			if((status = sender(argv[1]))!=0)
				printf("sending error\n");
		}
	}
	return 0;
}
