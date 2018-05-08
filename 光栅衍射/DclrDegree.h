#pragma once
#include <fstream>
#define pi 3.141592654

class Degree{
public:
	~Degree(){};
	Degree(): minite(0), second(0){}
	Degree(int mi,double se): minite{mi}, second{se}
		{ standize(); }
	Degree(int mi): minite{mi}, second{0} {}
	Degree(double num): minite{int(num)}, second{(num - int(num))*60}
		{ standize(); }
	
	int GetMinite()const;
	double GetSecond()const;
	double GetNum()const;
	void Modify(int mi,double se);
	void Modify(double num);
	void standize();
	void output(std::ostream &out,unsigned int pre=0)const;
	
	Degree operator+=(Degree t);
	Degree operator-=(Degree t);
private:
	int minite;
	double second;
};

Degree operator+(Degree a,Degree b);
Degree operator-(Degree a,Degree b);
Degree operator/(Degree t,int i);
std::ostream &operator<<(std::ostream &out,const Degree &t);
std::istream &operator>>(std::istream &in, Degree &t);

double dgr2arc(Degree t);
double sin(double theta,double pre=1e-8);