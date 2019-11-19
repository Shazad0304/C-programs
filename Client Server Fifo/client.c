#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int fd1; 
	int fd2; //file descriptor
 	char ab[15];
	char *srvrcmd = ab;  //server command will be stored
    char *serverfifo = "server123"; 
	char clinfo[15];  //clientinfo
        snprintf(clinfo, 15, "client%d", getpid()); // concatination process id with client
        printf("%s\n", clinfo); 
	mkfifo(clinfo,0666); //fifo will be create as clientprocessid
 
	
        fd1 = open(serverfifo,O_WRONLY); 
        write(fd1, clinfo, strlen(clinfo)+1); // writing client details to server's fifo
        close(fd1); 
	fd2 = open(clinfo,O_RDWR);
	while(1){
	read(fd2,srvrcmd,16);  //reading client fifo and checking for commands sent by server
	printf("%s\n",srvrcmd);
	system(srvrcmd);  //executiong server coomand
	}
	close(fd2);
	
    return 0; 
}
