#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int numOfDigits(int x)
{
	int c = 0;
	while(x!=0){
		x/=10;
		c++;
	}
	return c;
}

void append(char* a, char *str, int len, int start)
{
	for(int i=0;i<len;i++){
		a[start+i] = str[i];
	}
}

int main()
{
	char str[400] = "";
	int str_count = 0;
	int r=3, g=50, b=49;
	char c = 'A';
	int buf_size;

	for(int i=0;i<10;i++){
		buf_size = 10+2+numOfDigits(r)+numOfDigits(g)+numOfDigits(b);
		char buf[buf_size];
		snprintf(buf, 20, "\x1b[38;2;%d;%d;%dm%c%c", r,g,b,c,c);
		append(str,buf,buf_size,str_count);
		str_count+=buf_size;
		c+=1;
		r+=10;
		g+=10;
		b+=10;
	}
	str[str_count] = '\0';
	printf("%s\n",str);
	return 0;
}
