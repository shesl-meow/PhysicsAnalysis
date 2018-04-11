#include <iostream>
#include "method.h"

int main(){
	method(4,4,(char*)("table1.txt"));
	printf("\n---------------\n");
	method(4,4,(char*)("table2.txt"),&cylv);
	printf("\n---------------\n");
	method(6,1,(char*)("table3.txt"),&sphv);
	printf("\n---------------\n");
	method(3,2,(char*)("table4.txt"),&dsty);
	return 0;
}