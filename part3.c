#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>


#define BUFFER_SIZE 1024


int main(){
	char c[1]; 
	char reading[BUFFER_SIZE];
	char input[BUFFER_SIZE];
	int b, whence, offset, len, x;
	int fd;
	fd = open("/dev/simple_character_device", O_RDWR); //opening device with rw access
	if (fd < 0){
		printf("Could not open device\n");
		return -1;
	}
	
	while(1){
		printf("What would you like to do? (r, w, s, e)\n");
		scanf("%s", c);
		getchar();
		if (c[0]=='r'){
			//read
			printf("Enter the number of bytes you would like to read: \n");
			scanf("%d", &b);
			printf("You want to read %d bytes\n", b);
			printf("Squeaky Clean Buffer... %s\n", reading);
			read(fd, reading, b);
			memset(reading+b, '\0', strlen(reading)-b);
			printf("Reading... %s\n", reading);

		}
		else if (c[0]=='w'){
			//write
			printf("Enter data you would like to write: ");
			scanf("%[^\n]", input);
			//input[strlen(input)] = '\0'; //remove trailing next line
			printf("\nYou want to write %s\n", input);
			write(fd, input, strlen(input));
		}
		else if (c[0]=='s'){
			//seek
			printf("Enter an offset value: \n");
			scanf("%i", &offset);
			printf("Enter a whence value: \n");
			scanf("%i", &whence);
			lseek(fd, offset, whence);
		
		
		}
		else if (c[0]=='e'){
			return 0;
		}

	}

}
