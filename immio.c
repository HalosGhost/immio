/****************************************\
* Upload and manage images on imm.io     *
* License: CCPL Sam Stuewe, 2013 (BY-SA) *
\****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

FILE *url;
char command[256],output[256];
int len,i;
int n=16;
int v=0;

void usage(char *progname) {
	fprintf(stderr,"Usage: %s [-d|-v] image(s)\n",progname);
	fprintf(stderr,"   or: %s -r id token\n",progname);
	fprintf(stderr,"   or: %s -m id token name\n\n",progname);
	fprintf(stderr,"All arguments are mandatory for removing and renaming.\n");
	fprintf(stderr,"  -d   post direct links to images rather\n         than to landing pages.\n");
	fprintf(stderr,"  -h   print this help message.\n");
	fprintf(stderr,"  -r   remove identified image.\n");
	fprintf(stderr,"  -m   rename identified image.\n");
	fprintf(stderr,"  -v   be more verbose when printing\n         image information.\n\n");
	fprintf(stderr,"See `man %s` for more information.\n",progname);
	exit(44);
}

void upload(char *file,int lnk) {
	len=snprintf(command,sizeof(command),"curl -F image=@\"%s\" imm.io/store|cut -d \'\"\' -f%d",file,lnk);
	if (len<=sizeof(command)) {
		url=popen(command,"r");
		while (fgets(output,sizeof(output),url)) printf("%s\n",output);
		pclose(url);
	}
	else fprintf(stderr,"Command buffer too short");
}

void rmimg(char *id,char *token) {
	fprintf(stderr,"This option is under construction");
	// Remove identified image with associated token
	exit(1);
}

void mvimg(char *id,char *token, char *name) {
	fprintf(stderr,"This option is under construction");
	// Change identified image with associated token to have new name
	exit(1);
}

void insargs(int arglen) {
	fprintf(stderr,"This option requires %d arguments.\n",arglen);
	exit(1);
}

int main(int argc, char** argv) {
	if (argv[1]==NULL) usage(argv[0]);
	for (i = 1; i < argc; i++) {
		if (argv[i][0]=='-') {
			if (argv[i][1]=='\0') usage(argv[0]);

			else if (argv[i][1]=='h') usage(argv[0]);

			else if (argv[i][1]=='d') n=12;

			else if (argv[i][1]=='r') {
				if (argv[i+1]==NULL||argv[i+2]==NULL) insargs(2);
			    else rmimg(argv[i+1],argv[i+2]);
			}

			else if (argv[i][1]=='m') {
				if (argv[i+1]==NULL||argv[i+2]==NULL||argv[i+3]==NULL) insargs(3);
				else mvimg(argv[i+1],argv[i+2],argv[i+3]);
			}

			else if (argv[i][1]=='v') { v=1; fprintf(stderr,"Verbosity has not yet been implemented.\n"); }

			else fprintf(stderr,"Unrecognized option.\nSee `%s -h` or `man %s` for help.\n",argv[0],argv[0]);
		}
		else {
			upload(argv[i],n);
		}
	}
	return 0;
}
