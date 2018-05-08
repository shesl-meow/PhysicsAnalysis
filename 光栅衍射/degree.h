#pragma once
#include "time.h"

#define pi 3.141592654

double t2d(Time t)
{
	double res = t.GetNum();
	res *= pi/180;
	return res;
}

double sin(double theta,double pre=1e-8)
{
	double res1=theta, res2=0;
	double po=theta, sqr=-theta*theta;
	long long fac=1;
	unsigned int multi = 1;
	while(res1-res2>pre || res2-res1>pre)
	{
		res2 = res1;
		po *= sqr;
		multi += 2;
		fac *= multi*(multi-1);
		res1 += po/fac;
//		printf("po:%f\tfac:%ld\tres1:%lf\n",po,fac,res1);
	}
	return res1;
}