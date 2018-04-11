#include <iostream>
#include "../analysis.h"
#include <fstream>
using namespace std;

double t[3][4],l[2];

double ee(double v1,double v2,double u1,double u2){
	return abs(v1-v2)/abs(u1-u2);
}

int main(){
	cout<<"Debug!"<<endl;
	fstream infile("data.txt",ios::in);
	if(!infile.is_open()){
		cerr<<"open wrong!"<<endl;
		return 0;
	}
	for(int i=0; i<3; i++)
		for(int j=0; j<4; j++)
			infile>>t[i][j];
	for(int k=0; k<2; k++)
		infile>>l[k];
	infile.close();

	for(int i=0; i<3; i++){
		for(int j=0; j<4; j++)
			cout<<t[i][j]<<" ";
		cout<<endl;
	}
	for(int k=0; k<2; k++)
		cout<<l[k]<<" ";

	cout<<"\n\ne1"<<endl;
	for(int i=0; i<3; i++){
		double v1=l[0]/t[i][0],u2=l[1]/t[i][1];
		cout<<"v1:"<<v1<<"\nu2:"<<u2<<endl;	
		cout<<abs(v1/u2)<<endl;
	}

	return 0;
}