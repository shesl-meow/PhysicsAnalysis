#include <fstream>

double method2(double A,double d){
	return (A*A-d*d)/4/A;
}

int main(){
	std::fstream in("table1.1.txt",std::ios::in);
	if(!in.is_open()){
		return -1;
	}
	double x[2][2];
	for(int i=0; i<2; ++i)
		for(int j=0; j<2; ++j)
			in>>x[i][j];
	in.close();

	in.open("table1.2.txt",std::ios::in);
	if(!in.is_open()){
		return -1;
	}
	double s[2][4];
	for(int i=0; i<2; ++i)
		for(int j=0; j<4; ++j)
			in>>s[i][j];
	in.close();

	printf("The focus masured by method 1:%f\t%f\n",
			x[0][1]-x[0][0],x[1][1]-x[1][0]);
	printf("The focus masured by method 2:%f\t%f\n",
			method2(s[0][3]-s[0][0],s[0][2]-s[0][1]),
			method2(s[1][3]-s[1][0],s[1][2]-s[1][1])
			);
	return 0;
}
