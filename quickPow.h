#ifndef CSTDIO_INCLUDED
	#include<cstdio>
	#define CSTDIO_INCLUDED
#endif

template <typename T1, typename T2>
T1 quickPow(T1 down, T2 up) {
	if(up==1)return down;
	T1 pow=quickPow(down,up/2);
	if(up&1)return pow*pow*down;
	return pow*pow;
}
template <typename T1, typename T2, typename T3>
T1 quickPow(T1 down, T2 up, T3 mod) {
	if(up==1)return down%mod;
	T1 pow=quickPow(down,up/2)%mod;
	if(up&1)return (pow*pow)%mod*down%mod;
	return pow*pow%mod;
}
