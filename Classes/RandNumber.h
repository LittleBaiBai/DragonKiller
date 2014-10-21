
#ifndef __RAND_NUMBER_H__
#define __RAND_NUMBER_H__
#include "cocos2d.h"
#include <stdio.h>  
#include <time.h>
class RandNumber{
public:
	static float randFloat0_1();
	static float randFloat(float start, float end);
	static int randInt(int start, int end);
};
#endif