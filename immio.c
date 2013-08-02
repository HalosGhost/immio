/*******************************************\
* Simple program to upload images to imm.io *
* License: CCPL Sam Stuewe, 2013 (CC-BY-SA) *
\*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

FILE *url;
char command[256];
char output[256];
int len,i;
int n=16;

void usage(char *progname) {
	fprintf(stderr,"Usage: %s [-h|--help] [-d|--direct] <file1 [file2 ... fileN]>\n",progname);
	exit(44);
}

int main(int argc, char** argv) {
	if (argv[1]==NULL) usage(argv[0]);
	for (i = 1; i < argc; i++) {
		if (argv[i][0]=='-') {
			if (argv[i][1]=='h'||argv[i][2]=='h') usage(argv[0]);
			else if (argv[i][1]=='d'||argv[i][2]=='d') n=12;
		}
		else {
			len=snprintf(command,sizeof(command),"curl -F image=@\"%s\" imm.io/store|cut -d \'\"\' -f%d",argv[i],n);
			if (len<=sizeof(command)) {
				url=popen(command,"r");
				while (fgets(output,sizeof(output),url)) printf("%s\n",output);
				pclose(url);
			}
			else fprintf(stderr,"Command buffer too short");
		}
	}
	return 0;
}
