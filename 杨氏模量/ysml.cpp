#include "../method.h"
#include "funcDef.h"

int main(){
	const int tm = 6;
	double m[tm],h[2][tm],D[tm],B,b,l,ub[5];

	std::fstream in("data.txt",std::ios::in);
	if(!in.is_open()) return 0;
	for(int i=0; i<tm; ++i) in>>m[i];
	for(int i=0; i<tm; ++i) in>>h[0][i];
	for(int i=0; i<tm; ++i) in>>h[1][i];
	for(int i=0; i<tm; ++i) in>>D[i];
	in>>B>>b>>l;
	//多次测量的B类标准不确定度直接由仪器分辨率除以根号3
	for(int i=0; i<2; ++i){ in>>ub[i]; ub[i] /= sqrt(3.0);} 
	//单次测量时B类标准不确定度由仪器分辨率除以除以覆盖因子，米尺的覆盖因子为3
	for(int i=2; i<5; ++i){ in>>ub[i]; ub[i] /= 3;}
	in.close();

	double avgh[tm];
	printf("average h:\n");
	for(int i=0; i<tm; ++i){
		avgh[i] = (h[0][i] + h[1][i])/2;
		printf("%f\t",avgh[i]);
	}

	const int delt = tm/2;
	double delth[tm-delt],deltm[tm-delt];
	printf("\ndelt(hj)\tdelt(mj)\n");
	for(int i=0; i<tm-delt; ++i){
		delth[i] = avgh[i+delt]-avgh[i];
		deltm[i] = m[i+delt]-m[i];
		printf("%f\t%f\n",delth[i],deltm[i]);
	}
	
	printf("\n----------------------\n");
	printf("analysis sequence as below:\n");
	printf("B\t\tl\t\tdelt(mj)\tD\t\tb\t\tdelt(hj)\n");
	double *(DataRaw[]) = {&B,&l,&deltm[0],&D[0],&b,&delth[0]};
	int tmarray[] = {1,1,tm-delt,tm,1,tm-delt};
	double ubb[] = {ub[2],ub[4],0,ub[1],ub[3],ub[0]};
	method(&DataRaw[0],&tmarray[0],6,&ubb[0],&ysmlE);
	return 0;
}
