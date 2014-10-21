#ifndef GROUND_LAMA_SPRITE_H
#define GROUND_LAMA_SPRITE_H
#include "cocos2d.h"
#include "BaseLayer.h"
class GroundLamaSprite : public BaseLayer{
public:
	GroundLamaSprite();
	~GroundLamaSprite();
	static GroundLamaSprite* CreateWithAnimation();
	float runDistance;
	float up;
	float lamaScale;
	void RunAnimation(float distance);
	void MoveAnimation();	//²±×ÓÉìËõºÍ¶¯ÍÈ
	int isTouched(cocos2d::CCPoint);
    void setScale(float);
	cocos2d::CCSprite *lamaHead;
	cocos2d::CCSprite *lamaLeg;
private:
	
	cocos2d::CCArray *headAnimFrames;
	cocos2d::CCArray *legAnimFrames;
};



#endif