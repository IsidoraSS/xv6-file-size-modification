#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char *naziv="-1";
char *help="\nUse this program to encrypt a file using the set key.\nUsage: encr [OPTION]...\n\nCommand line options:\n\t-h, --help: Show help prompt.\n\t-a, --encrypt-all: Encrypt all files.\n";


int
main(int argc, char *argv[])
{
	int option = -1;
	for(int i=1;i<argc;i++){
		if((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) option = 0;
		else if((strcmp(argv[i], "-a") == 0) || (strcmp(argv[i], "--encrypt-all") == 0)) option = 1;
		else option=-1;
		switch(option){
			case 0:
				printf(help);
				exit();
				break;
			case 1:
				break;
			case -1:
				naziv=argv[i];
				break;
		}
	}
	int fd = open(naziv, O_RDWR);
	int ishod = encr(fd);
	switch (ishod)
	{
	case -1:
		printf("Failed to encrypt file: [%s] [key not set]\n", naziv);
		break;
	case -2:
		printf("Failed to encrypt file: [%s] [file type is T_DEV]\n", naziv);
		break;
	case -3:
		printf("Failed to encrypt file: [%s] [file already encrypted]\n", naziv);
		break;
	case 0:
		printf("Successfully encrypted file: [%s]\n", naziv);
	}
	close(fd);
	exit();
}
