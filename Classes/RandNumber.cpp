#include "RandNumber.h"

float RandNumber::randFloat0_1()
{ 
   clock_t tv;    
   tv = clock();  
   //根据时间产生随机种子
   //(这里加上一个rand函数，可解决在循环内(时间间隔极短)取随机数时，
   //连续取得的几个值相同的问题)
   unsigned int tsrans = tv + rand();
   srand(tsrans);    //设定随机数种子
   return CCRANDOM_0_1();
}

float RandNumber::randFloat(float start, float end){
	return RandNumber::randFloat0_1()*(end - start)+start;
}

int RandNumber::randInt(int start, int end){
	return RandNumber::randFloat0_1()*(end - start)+start;
}