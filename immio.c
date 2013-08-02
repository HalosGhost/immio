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
int len;

void usage(char *progname) {
	fprintf(stderr,"Usage: %s [-h|--help] <FILE>\n",progname);
	exit(44);
}

int main(int argc, char** argv) {
	if (argv[1]==NULL) usage(argv[0]);
	else if (argv[1][0]=='-') {
		if (argv[1][1]=='h'||argv[1][2]=='h') usage(argv[0]);
    }
	else {
		len=snprintf(command,sizeof(command),"curl -F image=@\"%s\" imm.io/store|cut -d \'\"\' -f12",argv[1]);
		if (len<=sizeof(command)) {
			url=popen(command,"r");
			while (fgets(output,sizeof(output),url)) printf("%s\n",output);
			pclose(url);
	    }
		else fprintf(stderr,"Command buffer too short");
    }
    return 0;
}
