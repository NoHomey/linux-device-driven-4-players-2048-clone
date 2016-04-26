#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(void) {
	if(wiringPiSetupGpio() == -1) {
                perror("error while seting up wiringPi\n");
                return 1;
        }
        printf("wringPi setup\n"); 
	int fd = serialOpen("/dev/ttyAMA0", 115200);
	int number;
	if(fd < 0) {
		perror("error while opening serial\n");
		return 1;
	}
	printf("serial opened\n");
	serialFlush(fd);
        printf("serial flushed\n");
	while(1) {
		number = serialDataAvail(fd);
		if(number == -1) {
			perror("error while counting avalible chars\n");
			return 1;
		}
		if(number > 0) {
			break;
		}
		serialPutchar(fd, 'i');
		sleep(2);
	}
	serialClose(fd);

	return 0;
}
