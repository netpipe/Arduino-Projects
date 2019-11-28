#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1
FILE *file;
int fileLen;
char *tmpbuffer;
void openport(void);
void readport(void);
void sendport(void);
int fd=0;
struct termios oldtp, newtp;
//char sendcmd1[256]="\0";
char buffer[512];

int main(){
//
	openport();
//	sleep(1);
	readport();
	sendport();
}


void sendport(void)
{
printf("enter write\n");
int n;
char *tmpbuffer = "g28";
fileLen = sizeof(tmpbuffer);//,//ftell(tmpbuffer);
//tmpbuffer = (char *)malloc(fileLen + 1);

//n = fwrite(fd, tmpbuffer, fileLen + 1);
putc (tmpbuffer , fd);

      //  arduino << "Hello from C++!";
	//arduino.close();

close(fd);

}

void sendgcode(void)
{
printf("enter write\n");
int n;
// sem_wait(&len);
file = fopen("sample.txt", "r");
//get file size
fseek(file, 0, SEEK_END);
fileLen = ftell(file);
fseek(file, 0, SEEK_SET);
tmpbuffer = (char *)malloc(fileLen + 1);
//read file contents
printf("Start send\n");
fread(tmpbuffer, fileLen, 1, file);
fclose(file);
n = write(fd, tmpbuffer, fileLen + 1);
if (n < 0)
{
	fputs("write() of bytes failed!\n", stderr);
}
else
{
	printf("Image sent successfully %d\n",n);
}
close(fd);

}

void openport(void)
fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY |O_NDELAY );
printf("Oviya %d\n",fd);
if (fd <0)
{
	perror(MODEMDEVICE);
 }
fcntl(fd,F_SETFL,0);
tcgetattr(fd,&oldtp); /* save current serial port settings */
// tcgetattr(fd,&newtp); /* save current serial port settings */
bzero(&newtp, sizeof(newtp));
// bzero(&oldtp, sizeof(oldtp));
newtp.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
newtp.c_iflag = IGNPAR | ICRNL;
newtp.c_oflag = 0;
newtp.c_lflag = ICANON;
newtp.c_cc[VINTR] = 0; /* Ctrl-c */
newtp.c_cc[VQUIT] = 0; /* Ctrl-\ */
newtp.c_cc[VERASE] = 0; /* del */
newtp.c_cc[VKILL] = 0; /* @ */
//newtp.c_cc[VEOF] = 4; /* Ctrl-d */
newtp.c_cc[VEOF] = 0; /* Ctrl-d */
newtp.c_cc[VTIME] = 0; /* inter-character timer unused */
newtp.c_cc[VMIN] = 1; /* blocking read until 1 character arrives */
newtp.c_cc[VSWTC] = 0; /* '\0' */
newtp.c_cc[VSTART] = 0; /* Ctrl-q */
newtp.c_cc[VSTOP] = 0; /* Ctrl-s */
newtp.c_cc[VSUSP] = 0; /* Ctrl-z */
newtp.c_cc[VEOL] = 0; /* '\0' */
newtp.c_cc[VREPRINT] = 0; /* Ctrl-r */
newtp.c_cc[VDISCARD] = 0; /* Ctrl-u */
newtp.c_cc[VWERASE] = 0; /* Ctrl-w */
newtp.c_cc[VLNEXT] = 0; /* Ctrl-v */
newtp.c_cc[VEOL2] = 0; /* '\0' */
// tcflush(fd, TCIFLUSH);
// tcsetattr(fd,TCSANOW,&newtp);
}


