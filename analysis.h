#pragma once
#define _tp_T_ template<class T>
#define pi 3.141592654

_tp_T_ T abs(T num,T zero=0){
	return (num>zero)?num:zero-num;
}

_tp_T_ T min(T *ar,int length){
	T mi = ar[0];
	for(int i=0; i<length; ++i)
		if( mi>ar[i] ) mi = ar[i];
	return mi;
}

_tp_T_ T max(T *ar,int length){
	T ma = ar[0];
	for(int i=0; i<length; ++i)
		if( ma<ar[i] ) ma = ar[i];
	return ma;
}

_tp_T_ T pow(T base,int power){
	T res=1;
	while( power ){
		if( power&1 ) res *= base;
		base *= base;
		power >>= 1;
	}
	return res;
}

_tp_T_ double sqrt(const T &num,double ac=1e-10){
	if(num<0) return 0;
	double res1=0,res2=num;
	while( abs(res1-res2)>ac ){
		res1 = res2;
		res2 = (res2+num/res2)/2;
	}
	return res2;
}

_tp_T_ T sum(const T *ar,const int &length){
	T res = 0;
	for(int i=0; i<length; ++i) res += ar[i];
	return res;
}

_tp_T_ T mean(const T *ar,const int &length){
	return sum(ar,length)/length;
}

_tp_T_ T var(const T *ar,const int &length){
	const T M = mean(ar,length);
	T var = 0;
	for(int i=0; i<length; ++i)
		var += pow(ar[i]-M,2);
	return var/length;
}

#define unbiaseVar ubvar
_tp_T_ T unbiaseVar(const T *ar,const int &length){
	if(length==1) return 0;
	const T M = mean(ar,length);
	T ubv = 0;
	for(int i=0; i<length; ++i)
		ubv += pow(ar[i]-M,2);
	return ubv/(length-1);
}

_tp_T_ T stan(const T *ar,const int &length){
	return sqrt( ubvar(ar,length) );
}

#define meanStan mstan
_tp_T_ T meanStan(const T *ar,const int &length){
	return sqrt( ubvar(ar,length)/length );
}

_tp_T_ T cov(const T *A,const T *B,const int &length){
	T res = 0;
	T mA=mean(A,length),mB=mean(B,length);
	for(int i=0; i<length; ++i)
		res += (A[i]-mA)*(B[i]-mB);
	return res/length;
}

#define unbiaseCov ubcov
_tp_T_ T unbiaseCov(const T *A,const T *B,const int &length){
	if(length==1) return 0;
	T res = 0;
	T mA=mean(A,length),mB=mean(B,length);
	for(int i=0; i<length; ++i)
		res += (A[i]-mA)*(B[i]-mB);
	return res/(length-1);
}

#define confDomain cfd
static const double confDomain[6]={1.84,1.32,1.2,1.14,1.11,1.09};
#define uncertainty ucty
_tp_T_ T uncertainty(const T *ar,const int &length){
	if(length>6) return -1;
	return cfd[length-1]*mstan(ar,length);
}

#define regression reg
_tp_T_ T regression(const T *A,const T *B,const int &length){
	T covAB = cov(A,B,length);
	T covBB = cov(B,B,length);
	return covAB/covBB;
}

#define BiaseOfReg BofR
_tp_T_ T BiaseOfReg(const T *A,
	const T *B, const unsigned int length){
	if(length<3) return 0;
	T cvab = cov(A,B,length),
		cvaa = cov(A,A,length),
		cvbb = cov(B,B,length);
	T R = cvab*cvab/(cvaa*cvbb);
	T k = cvab/cvbb;
	return k*sqrt( (1/R-1)/(length-2) );
}