#include <iostream>
#include "../analysis.h"
#include <fstream>

double t[3][4],l[2];

double ee(double v1,double v2,double u1,double u2){
	return abs(v1-v2)/abs(u1-u2);
}

int main(){
	std::fstream infile("data.txt",std::ios::in);
	if(!infile.is_open()) return 0;
	for(int i=0; i<3; i++)
		for(int j=0; j<4; j++)
			infile>>t[i][j];
	for(int k=0; k<2; k++) infile>>l[k];
	infile.close();

	for(int i=0; i<3; i++){
		for(int j=0; j<4; j++)
			printf("%f ",t[i][j]);
		printf("\n");
	}
	for(int k=0; k<2; k++) printf("%f ",l[k]);

	printf("\n\ncalculate e:\n");
	for(int i=0; i<3; i++){
		double v1=l[0]/t[i][0],v2=0,u1=0,u2=l[1]/t[i][1];
		printf("v1:%f\tu2:%f\te:%f\n",v1,u2,ee(v1,v2,u1,u2));
	}

	return 0;
}
