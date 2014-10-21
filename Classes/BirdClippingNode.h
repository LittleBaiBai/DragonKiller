#ifndef __BIRD_CLIPPINT_NODE_H__
#define __BIRD_CLIPPINT_NODE_H__

#define BIRD_MOVE_ACTION_TAG 1

#include "cocos2d.h"
#include "RandNumber.h"
#include "BaseLayer.h"
#include "BirdSystem.h"

class BirdClippingNode : public cocos2d::CCNode{
public:
	float xBirdMin;
	float yBirdMin;
	float xBirdMax;
	float yBirdMax;
	float birdScale;
	float birdHalfWidth, birdHalfHeight;
    
	cocos2d::CCAnimation* flyAnimation;
	cocos2d::CCTexture2D *birdTexture;
	cocos2d::CCSprite *bird;
	cocos2d::CCArray *birdAnimFrames;
	
	BirdClippingNode();
	void birdStartActions();
	void birdWander(float);
	int isAttacked(cocos2d::CCPoint target);
	int resumeOneHole(cocos2d::CCPoint target);
    void wearCrown();
};

#endif