#pragma once

typedef double(*func(double*,));

void method(
	const int tm,	//重复实验次数
	const int gp,	//待计算组数
	char* filename,	//数据所在文件名
	func synthesisF	//合成不确定度的函数
	)
{
	double *l[gp];
	double ub;
	fstream infile(filename,ios::in);
	if(!infile.is_open()) printf("open file failed!"),return;
	for(int i=0; i<gp; ++i) l[i] = new double[tm];
	for(int i=0; i<gp; ++i)
		for(int j=0; j<tm; ++j)
			infile>>l[j][i];
	infile>>ub;
	ub /= sqrt(3.0);
	infile.close();

	double avg[gp];
	printf("\naverage:\n");
	for(int i=0; i<gp; ++i) avg[i] = mean(l[i],tm), printf("%f\t",avg[i]);

	printf("\nstantard dev:\n");
	for(int i=0; i<gp; ++i) printf("%f\t",stan(l[i],tm));

	printf("\nmean standard dev:\n");
	for(int i=0; i<gp; ++i) printf("%f\t",mstan(l[i],tm));
	
	double ua[gp];
	printf("\nuncertianty(ua):\n");
	for(int i=0; i<gp; ++i) ua[i] = ucty(l[i],tm), printf("%f\t",ua[i]);
	
	printf("\nuncertianty(ub):%f",ub);

	double us[gp];
	printf("\nuncertianty(synthesis):\n");
	for(int i=0; i<gp; ++i){
		us[i] = synthesisF();
		printf("%f\t", us[i]);
	}

	printf("\n\n");
	for(int i=0; i<gp; ++i) delete []l[i];
}

sqrt( ua[i]*ua[i]+ub*ub )