#ifndef __MONSTER_SYS_H__
#define __MONSTER_SYS_H__
#include "cocos2d.h"
#include "GameLayer.h"
#include "GroundLamaSprite.h"
#include "GameWinLayer.h"
#include "BirdClippingNode.h"
#include "BaseLayer.h"

class GameLayer;
class MonsterSys : public BaseLayer{
public:
	float xBirdMin;
	float yBirdMin;
	float xBirdMax;
	float yBirdMax;
	float birdScale;
	cocos2d::CCImage *dragonImage;
	unsigned int *dragonPixels;
	GameLayer* gameLayer;
	cocos2d::CCSprite* dragon;
	cocos2d::CCSprite* dragonBg;
	cocos2d::CCArray* dragonHoleArray;
	cocos2d::CCProgressTimer* bloodBar;
	GroundLamaSprite* lama;
	cocos2d::CCClippingNode *dragonClipper;
	cocos2d::CCNode* dragonHolesStencil;
	cocos2d::CCTexture2D *birdTexture;	//避免重复生成对象
	cocos2d::CCArray *birdAnimFrames;

	MonsterSys();
	~MonsterSys();
	void initBird();
	void initDragon();
	void initBloodBar();
	void initGroundLama();
	void checkBloodBar();
	int addOneBird(int tag);
	void setGameLayer(GameLayer* GameLayer);
	void attackDragon(cocos2d::CCPoint attackPoint);
	void attackBird(cocos2d::CCPoint attackPoint);
	void setBloodPercentage(float percentage);
	//void bloodChangeCallBack(cocos2d::CCObject* ped);// 异步加载图片时 的回调函数
	void dragonRecover(cocos2d::CCSprite *holdStencilSprite);
};
#endif