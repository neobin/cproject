//read,write,close
#include <unistd.h>
//open
#include <fcntl.h>
//errno,阻塞返回的错误类型都要用到
#include <errno.h>
//strlen
#include <string.h>
//exit
#include <stdlib.h>
//perror,输出重定向
#include <stdio.h>

#define MSG_TRY "try again\n"

int main(void)
{
    char buf[10];
    int fd, n;

    //打开当前终端设备，也就是在当前终端的输入当作输入；非阻塞只读打开
    fd = open("/dev/tty", 0_RDONLY|O_NONBLOCK);

    //perror函数是stdio.h里面的错误处理函数，就是当文件没有打开的时候返回错误

    if(fd<0) {
            perror("open /dev/tty");
            exit(1); }
tryagain:
    n = read(fd, buf, 10);
    if (n < 0) {
        if (errno == EAGAIN) {
               sleep(3);
               write(STDOUT_FILENO, MSG_TRY,
                strlen(MSG_TRY));
               goto tryagain;
        }
        perror("read /dev/tty");
        exit(1);
}
    write(STDOUT_FILENO, buf, n);
    close(fd);
 return 0;
}