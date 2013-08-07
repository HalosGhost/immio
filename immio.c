/****************************************\
* Upload and manage images on imm.io     *
* License: CCPL Sam Stuewe, 2013 (BY-SA) *
\****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

FILE *url;
char command[256],uid[256],name[256],ext[256],size[256];
int len,i,width,height,dirlnk=0,verbose=0;

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
			fscanf(url,"%*[^i]id\": \"%[^\"]\",%*[^,],%*[^,],%*[^m]me\": \"%[^\"]\"%*[^x]xt\": \"%[^\"]\"%*[^:]: %d,%*[^:]: %d, %*[^:]: \"%[^\"]\"",uid,name,ext,&width,&height,size);
			pclose(url);
			fprintf(stdout,"link: ");
			if (uri) fprintf(stdout,"http://i.imm.io/%s.%s\n",uid,ext);
			else fprintf(stdout,"http://imm.io/%s\n",uid);
			if (verbose) {
				fprintf(stdout,"name: \"%s\"\n",name);
				fprintf(stdout,"dimensions: %dx%d\n",width,height);
				fprintf(stdout,"size: %s\n",size);
			}
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

				case 'v': verbose=1; break;
				default:
					fprintf(stderr,"Unrecognized option (%s).\nSee `%s -h` or `man %s` for help.\n",argv[i],argv[0],argv[0]);
					exit(1); break;
			}
		}
		else upload(argv[i],dirlnk);
	}
	return 0;
}
