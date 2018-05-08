#include "degree.h"
#include <iostream>

void testArg(char argv)
{
	if(argv < 2)
	{
		printf("At least one argument is required to be pass into.\n");
		exit(1);
	}
}
void testFile(std::fstream &in)
{
	if(!in.is_open())
	{
		printf("file open fail!\n");
		exit(2);
	}
}

int main(int argv,char **argc)
{
	testArg(argv);
	while(argv > 1)
	{
		std::fstream in(argc[1],std::ios::in);
		testFile(in);
		double GreenW = 0,d = 0;
		Time raw[6][3];
		in>>GreenW;
		for(int i=0; i<6; ++i)
		{
			for(int j=0; j<2; ++j)
				in>>raw[i][j];
			raw[i][2] = raw[i][0]-raw[i][1];
		}
		in.close();

		Time Avg[3],Half[3];
		for(int i=0; i<3; ++i)
		{
			Avg[i] = (raw[2*i][2]+raw[2*i+1][2])/2;
			Half[i] = Avg[i]/2;
		}
		d = GreenW/sin(t2d(Half[0]));
		double lambda[2] =
			{d*sin(t2d(Half[1]))/2, d*sin(t2d(Half[2]))/2};

		std::cout<<"green wavelength:\t"<<GreenW<<std::endl;
		std::cout<<"delta angle:\t"<<raw[0][2]<<"\t"<<raw[1][2]<<std::endl;
		std::cout<<"avrag angle:\t"<<Avg[0]<<std::endl;
		std::cout<<"half angle:\t"<<Half[0]<<std::endl;
		std::cout<<"const d:\t"<<d<<std::endl;

		std::cout<<"yellow light 1:\t"
			<<raw[2][2]<<"\t"<<raw[3][2]<<std::endl;
		std::cout<<"yellow light 2:\t"
			<<raw[4][2]<<"\t"<<raw[5][2]<<std::endl;
		std::cout<<"avrag angle 1:\t"<<Avg[1]<<std::endl;
		std::cout<<"avrag angle 2:\t"<<Avg[2]<<std::endl;
		std::cout<<"half angle:\t"<<Half[1]<<std::endl;
		std::cout<<"half angle:\t"<<Half[2]<<std::endl;
		std::cout<<"wavelength 1:\t"<<lambda[0]<<std::endl;
		std::cout<<"wavelength 2:\t"<<lambda[1]<<std::endl;
		
		--argv,++argc;
	}

}