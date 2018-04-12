#pragma once
#include <iostream>
#include <fstream>
#include "analysis.h"

/*
	计算二级指标函数指针定义
	传入值为两个浮点类型指针和整型常量（表示指针指向区域的大小）
	比如需要测量长宽高计算体积,传入长宽高的计算值和偏差
*/
typedef void(*func)(double*,double*,int);

_tp_T_ inline void empty(T *val,T *bia,int len){printf("\n");}
_tp_T_ void method(T **l,const int tm,const int gp,const T ub, func furtherF = &empty);

void method(
	const int tm,	//重复实验次数
	const int gp,	//待计算组数
	char* filename,	//数据所在文件名
	func furtherF = &empty	//合成不确定度的函数
	)
{
	double *(l[gp]);
	double ub;
	std::fstream infile(filename,std::ios::in);
	if(!infile.is_open()){ printf("open file failed!"); return; }
	for(int i=0; i<gp; ++i){
		l[i] = new double[tm];
		for(int j=0; j<tm; ++j)
			infile>>l[i][j];
	}
	infile>>ub;
	ub /= sqrt(3.0);
	infile.close();
	method(l,tm,gp,ub,furtherF);
	for(int i=0; i<gp; ++i) delete []l[i];
}

_tp_T_ void method(T **l,	//存储待分析数据的二维数组，每一行表示一个种类的变量
	const int tm,	//二维数组列数
	const int gp,	//二维数组行数
	const T ub,	//B类不确定度
	func furtherF = &empty	//合成不确定度的函数
	)
{
	T avg[gp];
	printf("average:\n");
	for(int i=0; i<gp; ++i) avg[i] = mean(l[i],tm), printf("%f\t",avg[i]);
	printf("\nstantard dev:\n");
	for(int i=0; i<gp; ++i) printf("%f\t",stan(l[i],tm));
	printf("\nmean standard dev:\n");
	for(int i=0; i<gp; ++i) printf("%f\t",mstan(l[i],tm));
	
	//A类不确定度计算
	T ua[gp];
	printf("\nuncertianty(ua):\n");
	for(int i=0; i<gp; ++i) ua[i] = ucty(l[i],tm), printf("%f\t",ua[i]);
	
	//B类不确定度打印
	printf("\nuncertianty(ub):%f",ub);

	//不确定度合成并计算
	T us[gp];
	printf("\nuncertianty(synthesis):\n");
	for(int i=0; i<gp; ++i) us[i] = sqrt( ua[i]*ua[i]+ub*ub ), printf("%f\t", us[i]);
	
	//计算二级指标
	furtherF(avg,us,gp);
}

//当各个自变量的对照实验组数不想等时
_tp_T_ void method(T **l,	//存储待分析数据的二维数组，每一行表示一个种类的变量
	int *tm,	//二维数组列数,即各个变量的实验次数
	const int gp,	//二维数组行数
	T *ub,	//B类不确定度
	func furtherF = &empty	//合成不确定度的函数
	)
{
	T avg[gp];
	printf("average:\n");
	for(int i=0; i<gp; ++i) avg[i] = mean(l[i],tm[i]), printf("%f\t",avg[i]);
	printf("\nstantard dev:\n");
	for(int i=0; i<gp; ++i) printf("%f\t",stan(l[i],tm[i]));
	printf("\nmean standard dev:\n");
	for(int i=0; i<gp; ++i) printf("%f\t",mstan(l[i],tm[i]));
	
	//A类不确定度计算
	T ua[gp];
	printf("\nuncertianty(ua):\n");
	for(int i=0; i<gp; ++i)
		ua[i] = ucty(l[i],tm[i]), printf("%f\t",ua[i]);
	
	//B类不确定度打印
	printf("\nuncertianty(ub):\n");
	for(int i=0; i<gp; ++i) printf("%f\t",ub[i]);

	//不确定度合成并计算
	T us[gp];
	printf("\nuncertianty(synthesis):\n");
	for(int i=0; i<gp; ++i) us[i] = sqrt( ua[i]*ua[i]+ub[i]*ub[i] ), printf("%f\t", us[i]);
	
	//计算二级指标
	furtherF(avg,us,gp);
}