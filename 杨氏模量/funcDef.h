#pragma once
#include "../analysis.h"

static const double g = 0.098;
void ysmlE(double *BlmDbh,double *biase,int gp=6)
{
	double E = 8*g/pi/BlmDbh[3];
	for(int i=0; i<3; ++i) E *= BlmDbh[i];
	for(int i=3; i<6; ++i) E /= BlmDbh[i];
	printf("\n\nysml:%f",E);
	
	double uv = 0;
	for(int i=0; i<3; ++i)
		uv += pow(E/BlmDbh[i]*biase[i],2);
	uv += pow(-2*E/BlmDbh[3]*biase[3],2);
	for(int i=4; i<6; ++i)
		uv += pow(-E/BlmDbh[i]*biase[i],2);
	uv = sqrt(uv);
	printf("\nbiase of ysml:%f\n",uv);
}