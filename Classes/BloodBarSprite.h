#ifndef __BLOOD_BAR_SPRITE_H__
#define __BLOOD_BAR_SPRITE_H__
#include "cocos2d.h"
#include "MonsterSys.h"
class BloodBarSprite:public cocos2d::CCProgressTimer{
public:
	int bloodDirection;
	BloodBarSprite();
	~BloodBarSprite();
	void setBloodPercentage(float);
	void bloodBarMove(float);
};
#endif