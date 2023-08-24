#include "../toplevel.h"
int codelen=1023;
//char * input = "(\\set{aa}{bb})$aa$";
int isoverflow = 0;
char * get_input(char* filename) {
	FILE * fp =fopen(filename, "r");
	if(fp==NULL){
		printf("Error opening file\n");
		abort();
	}
   char * input = malloc(sizeof(char)*1024);
   memset(input, 0, sizeof(char)*1024);
   char tmp[1024];
   int counter=0;
   for(int i;fgets(tmp, 1024, fp);){
		input=str_appened(input, tmp,&counter,&i);
   };
   codelen=strlen(input);
   return input;
   /*
   char * input = malloc(sizeof(char)*1024);
   memset(input, 0, sizeof(char)*1024);
   fgets(input, 1023, stdin);
   return input;*/
}
void donothing(char* fmt,...){
	//do nothing
}
char * str_appened(char * a, char * b, int * pret, int * max_len_plus_times){
	_dprintf("str_append called, %s %s %d %d %x %x\n", a, b, *pret, *max_len_plus_times, pret, max_len_plus_times);
	if(*pret+1+strlen(b) <= MAX_STR_LEN*(*max_len_plus_times)){
		strcpy(a+*pret,b);
		*pret+=strlen(b);
		return a;
	}else{
		*max_len_plus_times += 1;
		char * _ret = malloc(
			sizeof(char)*
			MAX_STR_LEN*
			(*(max_len_plus_times))
		);
		_dprintf("%x, %d\n",_ret,*(max_len_plus_times));
		memset(_ret, 0, MAX_STR_LEN*(*(max_len_plus_times)-1));
		strcpy(_ret,a);
		strcpy(_ret+*pret,b);
		*pret+=strlen(b);
		free(a);
				//free(tmp);
		return _ret;
	}
}
int _check_overflow(){
	return ctx.ip <= codelen ? 0 : 1;
}
void check_overflow(){
	if(_check_overflow()){
		printf("Overflowed! \n");
		abort();
		isoverflow = 1;
	}
}