#include <iostream>
#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main(){
	int fd_file, fd_area;
	char *memory, buff[1];
	struct stat filestat;
	char filename[100];
	int offset;
	int i = 0;

	fd_area = open("file.txt", O_RDWR);

	while(1){
		offset = lseek(fd_area, 0, SEEK_END);
		printf("Filename: ");
		scanf("%s", filename);

		stat(filename, &filestat);
		memory = (char *)mmap(0, filestat.st_size + offset, PROT_WRITE | PROT_READ, MAP_SHARED, fd_area, 0);
		ftruncate(fd_area, filestat.st_size + offset);

		while(read(fd_file, buff, 1) > 0){
			memory[offset + 1] =  buff[0];
			i++;
		}
	}
}