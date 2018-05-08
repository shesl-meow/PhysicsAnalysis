#pragma once
#include <iostream>
#include <fstream>

class Time{
public:
	Time(): minite(0), second(0){}
	Time(int mi,double se): minite{mi}, second{se} {}
	Time(int mi): minite{mi}, second{0} {}
	Time(double num): minite{int(num)}, second{(num - int(num))*60}{}
	
	int GetMinite()const{ return minite;}
	double GetSecond()const{ return second;}
	double GetNum()const{ return minite+second/60; }
	void Modify(int mi,double se){
		minite = mi, second = se;
		standize();
	}
	void Modify(double num){
		minite = int(num), second = (num - int(num))*60;
	}
	
	void standize()
	{
		int xin = int(double(second/60));
		minite += xin;
		second -= xin*60;
	}
	void output(std::ostream &out,unsigned int pre=0)const
	{
		double outsec = second;
		for(int i=0; i<pre; i++)
			outsec *= 10;
		outsec = double(int(outsec));
		for(int i=0; i<pre; i++)
			outsec /= 10;
		out<<minite<<"'"<<outsec<<"''";
	}
	
	Time operator+=(Time t)
	{
		minite += t.GetMinite();
		second += t.GetSecond();
		standize();
		return *this;
	}
	Time operator-=(Time t)
	{
		minite -= t.GetMinite();
		second -= t.GetSecond();
		standize();
		return *this;
	}
private:
	int minite;
	double second;
};

Time operator+(Time a,Time b)
{
	Time res = a;
	res += b;
	return res;
} 
Time operator-(Time a,Time b)
{
	Time res = a;
	res -= b;
	return res;
}
Time operator/(Time t,int i)
{
	double num = t.GetNum();
//	printf("%lf\n",num);
	num /= i;
	Time res(num);
	return res;
}
std::ostream &operator<<(std::ostream &out,const Time &t)
{
	t.output(out);
	return out;
}
std::istream &operator>>(std::istream &in, Time &t)
{
	int mi = 0; double se = 0;
	char buff[128]={'\0'};
	in >> buff;
//	printf("%s\n",buff);
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
//	t.output(std::cout);
	return in;
}