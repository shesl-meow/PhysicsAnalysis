#include "../method.h"

int main(){
	const int tm = 6;
	std::fstream in("data.txt",std::ios::in);
	if(!in.is_open()) return 0;
	double m[tm],h[2][tm],D[tm],B,b,l,ub[5];
	for(int i=0; i<tm; ++i) in>>m[i];
	for(int i=0; i<tm; ++i) in>>h[0][i];
	for(int i=0; i<tm; ++i) in>>h[1][i];
	for(int i=0; i<tm; ++i) in>>D[i];
	in>>B>>b>>l;
	for(int i=0; i<5; ++i){ in>>ub[i]; ub[i] /= sqrt(3.0);}
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
	double *tmp = &delth[0];
	method(&tmp,tm-delt,1,ub[0]);
	printf("\n----------------------\n");
	tmp = &D[0];
	method(&tmp,tm,1,ub[1]);
	printf("\n----------------------\n");
	return 0;
}
