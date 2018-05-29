#include"../method.h"

void S(double *val, double *bia, int len=3){
	double *S = new double[len];
	double *Sbia = new double[len];
	for(int i=0; i<len; i++){
		S[i] = pi*val[i]*val[i]/4;
		Sbia[i] = pi*val[i]*bia[i]/2;
	}
	printf("\nThe S of three: ");
	for(int i=0; i<len; i++)
		printf("\t%f",S[i]);
	printf("\nBiase of S: ");
	for(int i=0; i<len; i++)
		printf("\t%f",Sbia[i]);
	delete []S;
	delete []Sbia;
}


int main(int argc,char**argv){
	method(5,3,argv[1],&S);
	return 0;
}


