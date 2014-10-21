#ifndef FLY_LAMA_SPRITE_H
#define FLY_LAMA_SPRITE_H
#include "cocos2d.h"
#include "BaseLayer.h"
#include "RandNumber.h"
#include "GameLayer.h"

class FlyLamaSprite: public cocos2d::CCNode{
public:
	FlyLamaSprite(GameLayer *);
	~FlyLamaSprite();

	bool readyToAttack;
	float speed;
	float totalTime;

	void startMove();
	void Spit(cocos2d::CCPoint);
	float getHorizontalDist(float);

	cocos2d::CCSprite *lamaBody;
	cocos2d::CCSprite *lamaFace;
	cocos2d::CCSprite *lamaSaliva;
	void startCuttingDragon();
	void startCuttingBird(float);

private:
	float scale;
	float xMin;
	float xMax;
	float yMin;
	float yMax;
	float targetX;
	float targetY;
	float mouthToLeft;
	float mouthToDown;
	
	GameLayer* gameLayer;
	void WanderAnimation(float);
	void BlinkAnimation();
	void CloseMouth(float);
	void ChangeSaliva(float);
	
	void Attack();
};



#endif