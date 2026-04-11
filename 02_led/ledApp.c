#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

#define LED_ON 1
#define LED_OFF 0

int main(int argc, char *argv[])
{
	int fd, retvalue;
	char *filename;

	if(argc != 3){
		printf("Error Usage!\r\n");
		return -1;
	}else{
		printf("argc = %d\r\n", argc);
		printf("argv[0] = %s\r\n", argv[0]);
		printf("argv[1] = %s\r\n", argv[1]);
		printf("argv[2] = %s\r\n", argv[2]);
	}
	filename = argv[1];
	printf("filename = %s\r\n", filename);

	/* 打开驱动文件 */
	fd  = open(filename, O_RDWR);
	printf("fd = %d\r\n", fd);
	if(fd < 0){
		printf("Can't open file %s\r\n", filename);
		return -1;
	}

	if(atoi(argv[2]) == LED_ON){ /* 向驱动文件写入数据，打开 LED 灯 */
        retvalue = write(fd, argv[2], strlen(argv[2]));
        if(retvalue < 0){
            printf("write file %s failed!\r\n", filename);
        }else{
            printf("write file %s success!\r\n", filename);
        }
    }else if(atoi(argv[2]) == LED_OFF){ /* 向驱动文件写入数据，关闭 LED 灯 */
        retvalue = write(fd, argv[2], strlen(argv[2]));
        if(retvalue < 0){
            printf("write file %s failed!\r\n", filename);
        }else{
            printf("write file %s success!\r\n", filename);
        }
    }else{
        printf("Invalid argument for LED state. Use 1 for ON and 0 for OFF.\r\n");
    }


	/* 关闭设备 */
	retvalue = close(fd);
	if(retvalue < 0){
		printf("Can't close file %s\r\n", filename);
		return -1;
	}

	return 0;
}



