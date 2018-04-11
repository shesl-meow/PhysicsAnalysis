#pragma once
#include "../analysis.h"
#include "../method.h"

#define cylinderVolume cylv
void cylinderVolume(double *avg,double *us,int gp);
#define sphereVolume sphv
void sphereVolume(double *avg,double *us,int gp);
#define density dsty
void density(double *avg,double *us,int gp);

void cylv(double *avg,double *us,int gp){
	printf("\n\nthe volume:%f",pi*(avg[0]*avg[0]*avg[1]-avg[2]*avg[2]*avg[3])/4 );
	double uv = 0;
	uv += pow(2*avg[0]*avg[1]*us[0],2);
	uv += pow(avg[0]*avg[0]*us[1],2);
	uv += pow(2*avg[2]*avg[3]*us[2],2);
	uv += pow(avg[2]*avg[2]*us[3],2);
	uv = pi*sqrt(uv)/4;
	printf("\nbiase of volume:%f\n",uv);
}
void sphv(double *avg,double *us,int gp){
	double V = pi*pow(*avg,3)/6;
	printf("\n\nthe volume:%f",V);
	double uv = pi*(*avg)*(*avg)*(*us)/2;
	printf("\nbiase of volume:%f\n",uv);
}
void dsty(double *avg,double *us,int gp){
	printf("\n\nthe density:%f",avg[0]/avg[1]);
	double uv = 0;
	uv += pow( avg[0]/avg[1]/avg[1]*us[0],2 );
	uv += pow( avg[1]/avg[0]/avg[0]*us[1],2 );
	uv = sqrt(uv);
	printf("\nbiase of density:%f\n",uv);
}