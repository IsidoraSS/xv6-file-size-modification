#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int my_atoi(const char *str)
{
    int result = 0;
    int sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}



int kljuc=-1;
char *help="\nUse this program to set a encryption/decryption key.\nUsage: setkey [OPTION]...\n\nCommand line options:\n\t-h, --help: Show help prompt.\n\t-s, --secret: Activate secret mode.\n";

int
main(int argc, char *argv[])
{
	int option = -1;
	for(int i=1;i<argc;i++){
		if((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) option = 0;
		else if((strcmp(argv[i], "-s") == 0) || (strcmp(argv[i], "--secret") == 0)) option = 1;
		else option=-1;
		switch(option){
			case 0:
				printf(help);
				exit();
				break;
			case 1:
				//ovde echo
				break;
			case -1:
				kljuc = my_atoi(argv[i]);
				break;
		}
	}
	int ishod = setkey(kljuc);
	switch (ishod)
	{
	case -1:
		printf("Key value has to be >= 0!\n");
		break;
	case 0:
		break;
	}
	exit();
}
