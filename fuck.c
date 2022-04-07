#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// int countDigits(int x)
// {
// 	int c = 0;
// 	while(x!=0){
// 		x/=10;
// 		c++;
// 	}
// 	return c;
// }

// int main()
// {
// 	char* str = (char*)malloc(21*10+1);

// 	int r=3, g=50, b=49;
// 	char c = 'A';
// 	int buf_size;

// 	for(int i=0;i<10;i++){
// 		buf_size = 10+2+countDigits(r)+countDigits(g)+countDigits(b)+1;
// 		char buf[buf_size];
// 		snprintf(buf, 21, "\x1b[38;2;%d;%d;%dm%c%c", r,g,b,c,c);
// 		strcat(str, buf);
// 		r+=10;
// 		g+=10;
// 		b+=10;
// 		c+=1;
// 	}	

// 	printf("%s\n",str);
// 	// AABBCCDDEEFFGGHHIIJJ
// 	// printf("%ld\n", strlen("\x1b[38;2;255;255;255mQQ"));
// 	// printf("%ld\n", strlen("%s\033[0m"));

// 	free(str);

// 	return 0;
// }

// int main(int argc, char const *argv[])
// {
// 	system("clear");
// 	while(1){
// 		for(int i=0;i<10;i++){
// 			for (int j=0;j<10;j++){
// 				printf("x");
// 			}
// 			printf("\n");
// 		}
// 		sleep(1);
// 		system("echo \"\x1B[2;4H\"DEBIL");
// 		sleep(1);
// 		system("clear");
// 	}
// 	return 0;
// }

// typedef struct{
// 	int x, y;
// }debil;

// void adsa(debil d)
// {
// 	printf("%d\n", d.x);
// 	printf("%d\n", d.y);
// }

// int main(int argc, char const *argv[])
// {
// 	// debil d = {1,2};
// 	adsa(((debil){1,3}));
// 	return 0;
// }

int main(int argc, char const *argv[])
{
	// printf("%ld", strlen("\x1b[48;2;;;m\x1b[38;2;;;m\033[0m"));
	printf("\x1b[48;2;240;145;249m\x1b[38;2;255;124;111mQQ\033[0m");
	printf("\n");
	printf("\x1b[48;2;240;145;249m\x1b[38;2;32;32;3mWW\033[0m");
	return 0;
}