#include "RandNumber.h"

float RandNumber::randFloat0_1()
{ 
   clock_t tv;    
   tv = clock();  
   //����ʱ������������
   //(�������һ��rand�������ɽ����ѭ����(ʱ��������)ȡ�����ʱ��
   //����ȡ�õļ���ֵ��ͬ������)
   unsigned int tsrans = tv + rand();
   srand(tsrans);    //�趨���������
   return CCRANDOM_0_1();
}

float RandNumber::randFloat(float start, float end){
	return RandNumber::randFloat0_1()*(end - start)+start;
}

int RandNumber::randInt(int start, int end){
	return RandNumber::randFloat0_1()*(end - start)+start;
}