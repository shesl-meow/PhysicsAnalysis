#include <iostream>
#include <fstream>
#include "../analysis.h"
using namespace std;
const double c = 4.1868, c1 = 0.385, c2 = 0.370, m2=0.02;
double calS(double *tp,double *tm,double t,int length){
	printf("\n-------------------------------\n");
	double mini = min(tp,length), S = 0;
	for(int i=0; tp[i]!=mini; ++i){
		S += ((tp[i]+tp[i+1])/2-t) * (tm[i+1]-tm[i]) ;
		printf("first %d Area S: %f\n",i+1,S);
	}
	printf("curve reach the bottom firstly.");
	printf("\n-------------------------------\n");
	return S;
}

int main(){
	fstream in("line.txt");
	if( !in.is_open() ){
		printf("open file fail!");
		return 0;
	}

	double Troom,m[3],tp1[6],tm1[6],tp2[18],tm2[18];
	in>>Troom;
	for(int i=0; i<3; ++i) in>>m[i];
	for(int i=0; i<6; ++i) tm1[i] = i, in>>tp1[i];
	for(int i=0; i<18; ++i) tm2[i] = i*10, in>>tp2[i];
	in.close();
	
	cout<<"m-table:"<<endl;
	printf("%f\t%f\t%f\t%f\t%f",m[0],m[1],m[1]-m[0],m[2],m[2]-m[1]);

	cout<<"\n-------------------------------\n";
	cout<<"regression:"<<endl;
	double k = reg(tp1,tm1,6),b = mean(tp1,6)-k*mean(tm1,6);
	printf( "tp1 = %f*tm1 + %f\n",k,b );
	tp2[0] = k*6+b;
	printf( "when tm1=6min : %f",k*6+b);

	cout<<"deltaS:\t"<<calS(tp2,tm2,Troom,18)<<endl;
	cout<<"L:\t"<<(c*(m[1]-m[0])+c1*m[0]+c2*m2)*(tp2[0]-min(tp2,18))
		/( m[2]-m[1] )-c*min(tp2,18);
	return 0;
}