#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int brojBlokova=150;
char *naziv="long.txt";

char *help="\nUse this program to create a big file filled with a-z characters.\nDefault filename: long.txt\nDefault blocks: 150\nUsage: blockwriter [OPTION]...\n\nCommand line options:\n\t-h, --help: Show help prompt.\n\t-b, --blocks: Number of blocks to write.\n\t-o, --output-file: Set output filename.\n";


void blockwriter(){
	char abeceda[BSIZE];
	for(int i=0;i<BSIZE;i++){
		abeceda[i]='a'+i%26;
	}

	int fd = open(naziv, O_CREATE | O_RDWR);

	for(int i=1; i<=brojBlokova; i++){
		printf("Writing block %d\n", i);
		if(i==brojBlokova){
			abeceda[BSIZE-1]='\n';
		}
		write(fd, abeceda, BSIZE);
	}

	close(fd);
}

int
main(int argc, char *argv[])
{
	int option = -1;
	for(int i=1;i<argc;i++){
		if((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) option = 0;
		else if((strcmp(argv[i], "-b") == 0) || (strcmp(argv[i], "--blocks") == 0)) option = 1;
		else if((strcmp(argv[i], "-o") == 0) || (strcmp(argv[i], "--output-file") == 0)) option = 2;
		else option=-1;
		switch(option){
			case 0:
				printf(help);
				exit();
				break;
			case 1:
				brojBlokova = atoi(argv[i+1]);
				if(brojBlokova <= 0) brojBlokova = 150;
				i+=1;
				break;
			case 2:
				naziv = argv[i+1];
				if(strlen(naziv) == 0) naziv="long.txt";
				i+=1;
				break;
			case -1:
				continue;
				break;
		}
	}
	blockwriter();
	exit();
}
