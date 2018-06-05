#include"../regmethod.h"

int main(int argv,char *argc[]){
	while( argv>1 )
	{
		regmethod(argc[1]);
		argv--,argc++;
	}
	return 0;
}
