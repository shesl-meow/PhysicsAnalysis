#include "../../method.h"

int main(int argc,char **argv)
{
	const int len = 7;
	double vol[len],S[len];
	while( argc>1 )
	{
		std::fstream in(argv[1],std::ios::in);
		if(!in.is_open())
		{
			printf("print file failed!");
			exit(1);
		}
		for(int i=0; i<len; ++i)
			in>>vol[i];
		for(int i=0; i<len; ++i)
			in>>S[i];
		in.close();

		double k = regression(S,vol,len);
		printf("regression(if S=k*vol):%f\n",k);
		double bia = BofR(S,vol,len);
		printf("biase of regression(if S=k*vol):%f\n",bia);
		argc--,argv++;
	}
}
