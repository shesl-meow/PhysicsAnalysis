#include "DclrDegree.h"
#include <iostream>

static int floor(double a)
{
	double del = a - int(a);
	return del>=0 ? int(a) : int(a)-1;
}

int Degree::GetMinite()const{ return minite;}
double Degree::GetSecond()const{ return second;}
double Degree::GetNum()const{ return minite+second/60; }

void Degree::Modify(int mi,double se){
	minite = mi;
	second = se;
	standize();
}

void Degree::Modify(double num){
	minite = int(num);
	second = (num - int(num))*60;
	standize();
}

void Degree::standize()
{
	int xin = floor(double(second/60));
	minite += xin;
	second -= xin*60;
}

void Degree::output(std::ostream &out,unsigned int pre)const
{
	double outsec = second;
	for(int i=0; i<pre; i++)
		outsec *= 10;
	outsec = double(int(outsec));
	for(int i=0; i<pre; i++)
		outsec /= 10;
	out<<minite<<"'"<<outsec<<"''";
}	

Degree Degree::operator+=(Degree t)
{
	minite += t.GetMinite();
	second += t.GetSecond();
	standize();
	return *this;
}

Degree Degree::operator-=(Degree t)
{
	minite -= t.GetMinite();
	second -= t.GetSecond();
	standize();
	return *this;
}

Degree operator+(Degree a,Degree b)
{
	Degree res = a;
	res += b;
	return res;
} 

Degree operator-(Degree a,Degree b)
{
//	std::cout<<a<<"\t"<<b<<"\n";
	return a -= b;
}

Degree operator/(Degree t,int i)
{
	return Degree( t.GetNum()/i );
}

std::ostream& operator<<(std::ostream &out,const Degree &t)
{
	t.output(out);
	return out;
}

std::istream& operator>>(std::istream &in, Degree &t)
{
	int mi = 0; double se = 0;
	char buff[128]={'\0'};
	in >> buff;
	int i;
	for(i=0; buff[i]!='\''; ++i)
	{
		if(buff[i]<'0' || buff[i]>'9' || i>127) return in;
		mi *= 10;
		mi += int(buff[i]-'0');
	}
	++i;
	for(int pos=1; buff[i]!='\''; ++i)
	{
		if(buff[i] == '.') pos *= 10;
		else if(buff[i]<'0' || buff[i]>'9' || i>127) return in;
		
		if( pos==1 )
		{
			se *= 10;
			se += int(buff[i]-'0');
		}else{
			se += double(buff[i]-'0')/pos;
			pos *= 10;
		}
	}
	if(buff[i+1] != '\'') return in;
	t.Modify(mi,se);
	return in;
}

double dgr2arc(Degree t)
{
	double res = t.GetNum();
	res *= pi/180;
	return res;
}

double sin(double theta,double pre)
{
	double res1=theta, res2=0;
	double po=theta, sqr=-theta*theta;
	long long fac=1;
	unsigned int multi = 1;
	while(res1-res2>pre || res2-res1>pre)
	{
		res2 = res1;
		po *= sqr;
		multi += 2;
		fac *= multi*(multi-1);
		res1 += po/fac;
	}
	return res1;
}