#pragma once
#include <iostream>
#include <fstream>
#include "../analysis.h"

/*
	计算二级指标函数指针定义
	传入值为两个浮点类型指针和整型常量（表示指针指向区域的大小）
	比如需要测量长宽高计算体积,传入长宽高的计算值和偏差
*/
typedef void(*func)(double*,double*,int);

void empty(double *val,double *bia,int len){printf("\n");}
#define cylinderVolume cylv
void cylinderVolume(double *avg,double *us,int gp);
#define sphereVolume sphv
void sphereVolume(double *avg,double *us,int gp);
#define density dsty
void density(double *avg,double *us,int gp);


void method(
	const int tm,			//重复实验次数
	const int gp,			//待计算组数
	char* filename,			//数据所在文件名
	func furtherF = &empty	//合成不确定度的函数
	)
{
	double l[gp][tm];
	double ub;
	std::fstream infile(filename,std::ios::in);
	if(!infile.is_open()){ printf("open file failed!"); return; }
	for(int i=0; i<gp; ++i)
		for(int j=0; j<tm; ++j)
			infile>>l[i][j];
	infile>>ub;
	ub /= sqrt(3.0);
	infile.close();

	double avg[gp];
	printf("average:\n");
	for(int i=0; i<gp; ++i) avg[i] = mean(l[i],tm), printf("%f\t",avg[i]);
	printf("\nstantard dev:\n");
	for(int i=0; i<gp; ++i) printf("%f\t",stan(l[i],tm));
	printf("\nmean standard dev:\n");
	for(int i=0; i<gp; ++i) printf("%f\t",mstan(l[i],tm));
	
	//A类不确定度计算
	double ua[gp];
	printf("\nuncertianty(ua):\n");
	for(int i=0; i<gp; ++i) ua[i] = ucty(l[i],tm), printf("%f\t",ua[i]);
	
	//B类不确定度打印
	printf("\nuncertianty(ub):%f",ub);

	//不确定度合成并计算
	double us[gp];
	printf("\nuncertianty(synthesis):\n");
	for(int i=0; i<gp; ++i) us[i] = sqrt( ua[i]*ua[i]+ub*ub ), printf("%f\t", us[i]);
	
	//计算二级指标
	furtherF(avg,us,gp);
}


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