#ifndef __BIRD_SYSTEM_H__
#define __BIRD_SYSTEM_H__
#include "cocos2d.h"
#include "BaseLayer.h"
#include "BirdClippingNode.h"
#include "GameLayer.h"

class GameLayer;
class BirdClippingNode;

class BirdSystem : public BaseLayer{
public:
	float xBirdMin;
	float xBirdMax;
	float yBirdMin;
	float yBirdMax;
	int maxBirdNumber;
	GameLayer* gameLayer;
	cocos2d::CCTexture2D* birdTexture;
	cocos2d::CCArray* birdAnimFrames;
	cocos2d::CCArray* birdArray;
	float birdScale;
	int removeBirdIndex;
	BirdClippingNode* resumeBird;

	BirdSystem();
	void setGameLayer(GameLayer* layer);
	void addOneBird(float);
	void showBirds();
	void recoverDragon();
	void resumeOneHole(float);
	void afterResumeOneHole(float);
	int attackBird(cocos2d::CCPoint target);
	void removeBird(float);
    bool tooManyBirds();
};

#endif