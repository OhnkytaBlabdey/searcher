#include<stdio.h>
#include<string.h>

char buf[4096];
char buf2[4096];

int main()
{
	*buf2=0;
	while(gets(buf)>0){
		if(strstr(buf,"win")>0) return 1;
		else if(strcmp(buf,buf2) ==0 ) return 2;
		strcpy(buf2,buf);
	}
	return 0;
}