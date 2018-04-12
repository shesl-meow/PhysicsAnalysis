#pragma once
#include "../analysis.h"

void regF(double*A,double*B,const int l)
{

	double covAB = cov(A,B,l);
	double covAA = cov(A,A,l);
	double covBB = cov(B,B,l);
	double a = mean(A,l);
	double b = mean(B,l);
	double *sA = new double[l],*sB = new double[l];
	for(int i=0; i<l; ++i)
		sA[i] = A[i]*A[i], sB[i] = B[i]*B[i];

	printf("related coeffient:%f\n",covAB*covAB/(covAA*covBB));

	printf("\nA = %f*B + %f",covAB/covBB,a-covAB*b/covBB);
	printf("\nbiased of reg-coef:%f",BofR(A,B,l));
	printf("\nbiased of intercept:%f",sqrt(mean(sA,l))*BofR(A,B,l));

	printf("\nB = %f*A + %f",covAB/covAA,b-covAB*a/covAA);
	printf("\nbiased of reg-coef:%f",BofR(B,A,l));
	printf("\nbiased of intercept:%f",sqrt(mean(sB,l))*BofR(B,A,l));
	
	delete []sB;
	delete []sA;
}