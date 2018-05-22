#pragma once
#include "../../method.h"

static const double nA = 0.01;
static const double pc = 1e-3;
static const double p0 = 1e-3;

void calS(double *dt,double *bia,const int gp=3)
{
	double S = (dt[2]/nA)/(dt[1]/dt[0]);
	printf("\nS:%f\n",S);
	double p1 = sqrt(pc*pc + p0*p0 + pow(0.1/S,2));
	double p2 = sqrt(pc*pc + pow(0.1/S,2));

	printf("if state1--p1:%f\tAnd absolute biase:%f\n",p1,dt[0]*p1);
	printf("if combine two--p2:%f\tAnd absolute biase:%f\n",p2,dt[0]*p2);
}
