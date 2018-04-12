#include <iostream>
#include <fstream>
#include "regDef.h"
#include "../method.h"

const double g = 9.8;
int main(){
	method(4,1,(char*)"table1.txt");
	printf("\n------------------------\n");

	std::fstream input("table2.txt",std::ios::in);
	if( !input.is_open() ) return 0;
	const int l = 6;
	double A[l],B[l],p;
	for(int i=0; i<l; ++i){
		input>>A[i];
		A[i] = sqrt(A[i]*g);
	}
	for(int i=0; i<l; ++i) input>>B[i];
	input>>p;
	input.close();

	regF(A,B,l);
	return 0;
}