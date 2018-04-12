#include <iostream>
#include <fstream>
#include "regDef.h"

const double p = 0.000656;
const double g = 9.8;
int main(){
	std::fstream input("table2.txt");
	if( !input.is_open() ){
		std::cerr<<"input file fail!";
		return -1;
	}
	const int l = 6;
	double A[l],B[l];
	for(int i=0; i<l; i++)
		input>>A[i]>>B[i];
	input.close();

	return 0;
}