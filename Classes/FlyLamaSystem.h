#ifndef FLY_LAMA_SYSTEM_H
#define FLY_LAMA_SYSTEM_H
#include "cocos2d.h"
#include "BaseLayer.h"
#include "GameLayer.h"
#include "FlyLamaSprite.h"
class GameLayer;
class FlyLamaSystem : public BaseLayer{
public:
	FlyLamaSystem();
	~FlyLamaSystem();
	void setGameLayer(GameLayer* gameLayer);
	void produceLamas(int count);
	void showLamas(int count);
	void TouchToSpit(cocos2d::CCPoint);

	cocos2d::CCArray* getLamaArray();
private:
	GameLayer *gameLayer;
	cocos2d::CCArray *flyingLamas;
};


#endif