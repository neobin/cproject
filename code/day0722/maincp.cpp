#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MSG_TRY "try again\n"
#define BUFF_SIZE 10

int main(){
	char buf[BUFF_SIZE];
	int fd,n;


	fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
	if(fd < 0){
		perror("open try again");
		exit(1);
	}

tryagain:
	n = read(fd,buf,BUFF_SIZE);
	if(n < 0){
		if(errno == EAGAIN){
			sleep(3);
			write(STDOUT_FILENO,MSG_TRY,strlen(MSG_TRY));
			goto tryagain;
		}
		perror("read /dev/tty");
		exit(1);
	}
	write(STDOUT_FILENO,buf,BUFF_SIZE);
	close(fd);
	return 0;
}