#include <iostream>
#include "../analysis.h"
#include <fstream>

const double p = 0.000656;
int main(){
	std::fstream input("data.txt");
	if( !input.is_open() ){
		std::cerr<<"input file fail!";
		return -1;
	}
	const int l = 6;
	double A[l],B[l];
	for(int i=0; i<l; i++)
		input>>A[i]>>B[i];
	input.close();

	double covAB = cov(A,B,l);
	double covAA = cov(A,A,l);
	double covBB = cov(B,B,l);
	double a = mean(A,l);
	double b = mean(B,l);
	double *sA = new double[l],*sB = new double[l];
	for(int i=0; i<l; ++i)
		sA[i] = A[i]*A[i], sB[i] = B[i]*B[i];

	std::cout<<"related coeffient:"<<
		covAB*covAB/(covAA*covBB)<<std::endl;
	std::cout<<"\nregression coeffient,A=f(B):"<<covAB/covBB<<
		"\nintercept:"<<a-covAB*b/covBB<<
		"\nbiased of reg-coef:"<<BofR(A,B,l)<<
		"\nbiased of intercept:"<<sqrt(mean(sA,l))*BofR(A,B,l)<<std::endl;

	std::cout<<"\nregression coeffient,B=f(A):"<<
		covAB/covAA<<"\nintercept:"<<b-covAB*a/covAA<<
		"\nbiased of reg-coef:"<<BofR(B,A,l)<<
		"\nbiased of intercept:"<<sqrt(mean(sB,l))*BofR(B,A,l)<<std::endl;

		delete []sA;
		delete []sB;
	return 0;
}