#include"utils.h"

int SRAND_CALL=0;

int EnguinApi_Utils_GetTicks()
{
	return time(NULL)*1000;
}

int EnguinApi_Utils_CompareArrays(int* arr1, int* arr2, int len)
{
	int i;
	for(i=0;i<len;i++){
		if(arr1[i]!=arr2[i]){
			return 0;
		}
	}
	return 1;
}

int EnguinApi_Utils_RandomNumber(int start, int stop)
{
	if(SRAND_CALL!=-1){
		srand(time(0));
		SRAND_CALL = -1;
	}
	return (rand()%(stop-start+1))+start;
}

int EnguinApi_Utils_CountDigits(int n)
{
	int c = 0;
	while(n!=0){
		n/=10;
		c++;
	}
	return c;
}

void EnguinApi_Utils_Sleep(float miliseconds)
{
	int micros = (int)(miliseconds*1000);
	usleep(micros);
}

EnguinApi_Utils_Buffer EnguinApi_Utils_Buffer_Create(int size, int maxLength)
{
	EnguinApi_Utils_Buffer buff;
	buff.size = size;
	buff.maxLength = maxLength;
	buff.string = (char*)malloc(size*maxLength*sizeof(char));
	for(int i=0;i<size;i++){
		*(buff.string+i*maxLength) = '\0';
	}
	return buff;
}

char* EnguinApi_Utils_Buffer_Get(EnguinApi_Utils_Buffer* buff, int id)
{
	return buff->string+id*buff->maxLength;
}

void EnguinApi_Utils_Buffer_Set(EnguinApi_Utils_Buffer* buff, int id, char* str)
{
	int i;
	if((int)strlen(str)<=buff->maxLength){
		for(i=0;i<buff->maxLength;i++){
			if(i<=(int)strlen(str)){
				*(buff->string+id*buff->maxLength+i) = *(str+i);
			}
			else{
				*(buff->string+id*buff->maxLength+i) = ' ';
			}
		}
	}
}

void EnguinApi_Utils_Kill()
{
	system("reset");
	_exit(0);
}
