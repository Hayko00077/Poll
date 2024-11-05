#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/poll.h>
#define TIMEVAL 2
int main() {
	const int fileDescript = 6;
	struct pollfd fds[fileDescript];
	int fd1,fd2,fd3,fd4,fd5,fd6;
	
	fd1 = open("1.txt",O_WRONLY);
	fd2 = open("2.txt",O_RDONLY);
	fd3 = open("3.txt",O_WRONLY);
	fd4 = open("4.txt",O_RDONLY);
	fd5 = open("5.txt",O_WRONLY);
	fd6 = open("6.txt",O_RDONLY);

	fds[0].fd = fd1;
	fds[0].events = POLLOUT;
	
	fds[1].fd = fd2;
	fds[1].events = POLLIN;

	fds[2].fd = fd3;
	fds[2].events = POLLOUT;

	fds[3].fd = fd4;
	fds[3].events = POLLIN;

	fds[4].fd = fd5;
	fds[4].events = POLLOUT;

	fds[5].fd = fd6;
	fds[5].events = POLLIN;

	int pl = poll(fds,fileDescript,TIMEVAL);

	if (pl < 0) {
		perror("poll()");
		exit(1);
	}
	for (int i = 0; i < fileDescript; ++i) {
		if (fds[i].revents & POLLIN) {
			printf("this file descriptor %d readable\n",fds[i].fd);
		} else if (fds[i].revents & POLLOUT) {
			printf("this file descriptor %d writable\n",fds[i].fd);
		}
	}
	for (int i = 0; i < fileDescript; ++i) {
		close(fd1++);
	}

}
