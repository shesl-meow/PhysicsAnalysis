#pragma once
#include <iostream>
#include <fstream>
#include "analysis.h"

/*
	计算二级指标函数指针定义
	传入值为两个浮点类型指针和整型常量（表示指针指向区域的大小）
	比如需要测量长宽高计算体积,传入长宽高的计算值和偏差
*/
_tp_T_ typedef void(*func)(T*,T*,int);

_tp_T_ void empty(T *val,T *bia,int len){printf("\n");}
_tp_T_ void method(T **l,const int tm,const int gp, func furtherF = &empty);

_tp_T_ void method(
	const int tm,	//重复实验次数
	const int gp,	//待计算组数
	char* filename,	//数据所在文件名
	func furtherF = &empty	//合成不确定度的函数
	)
{
	T l[gp][tm];
	T ub;
	std::fstream infile(filename,std::ios::in);
	if(!infile.is_open()){ printf("open file failed!"); return; }
	for(int i=0; i<gp; ++i)
		for(int j=0; j<tm; ++j)
			infile>>l[i][j];
	infile>>ub;
	ub /= sqrt(3.0);
	infile.close();
	method(l,tm,gp,furtherF);
}

_tp_T_ void method(T **l,	//存储待分析数据的二维数组，每一行表示一个种类的变量
	const int tm,	//二维数组列数
	const int gp,	//二维数组行数
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