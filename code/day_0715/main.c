#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int fd;

	fd = open("./test.txt",0_RDWR,0_CREAT);

	close(fd);

	return 0;
}

