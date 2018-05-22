#include"funcDef.h"

int main(int argc,char**argv){
	while( argc>1 )
	{
		method(1,3,argv[1],&calS);
		argc--,argv++;
	}
	return 0;
}
