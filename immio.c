/****************************************\
* Upload and manage images on imm.io     *
* License: CCPL Sam Stuewe, 2013 (BY-SA) *
\****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

FILE *url;
char command[256],payload[256];
int len,i;
int dirlnk=0;
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

void upload(char *file,int uri) {
	len=snprintf(command,sizeof(command),"curl -F image=@\"%s\" imm.io/store",file);
	if (len<=sizeof(command)) {
		if ( (url=popen(command,"r")) ) {
			if ( uri=='1' ) fscanf(url,"%*s \"link\": \"%s\"",payload); // Read in direct link
			else fscanf(url,"%*s \"uri\": \"%s\"",payload); // Read in landing page link
			pclose(url);
			fprintf(stdout,"%s\n",payload);
		}
		else { fprintf(stderr,"Upload Failed\n");exit(1); }
	}
	else { fprintf(stderr,"Command buffer too short\n"); exit(1); }
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
	fprintf(stderr,"This option requires %d argument(s).\n",arglen);
	exit(1);
}

int main(int argc, char** argv) {
	if ( !argv[1] ) usage(argv[0]);
	for ( i = 1; i < argc; i++ ) {
		if ( argv[i][0]=='-' ) {
			switch ( argv[i][1] ) {
				case 'h': usage(argv[0]); break;
				case 'd': dirlnk=1; break;
				case 'r':
					if ( argv[i+1] && argv[i+2] ) rmimg(argv[i+1],argv[i+2]);
					else insargs(2); break;

				case 'm':
					if ( argv[i+1] && argv[i+2] && argv[i+3] ) mvimg(argv[i+1],argv[i+2],argv[i+3]);
					else insargs(3); break;

				case 'v': v=1; fprintf(stderr,"Verbosity has not yet been implemented.\n");	break;
				default:
					fprintf(stderr,"Unrecognized option.\nSee `%s -h` or `man %s` for help.\n",argv[0],argv[0]);
					exit(1); break;
			}
		}
		else upload(argv[i],dirlnk);
	}
	return 0;
}
