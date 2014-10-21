#ifndef __DEFENDERGAME_LAYER_H__
#define __DEFENDERGAME_LAYER_H__
#include "BaseLayer.h"
#include "GameBackground.h"
#include "MonsterSys.h"
#include "FlyLamaSystem.h"
#include "BirdSystem.h"
#include "PauseLayer.h"
#include "AboutCoderLayer.h"
#include "GameOverLayer.h"
//#include "SimpleAudioEngine.h"

// 这个类是游戏主类
class MonsterSys;
class FlyLamaSystem;
class BirdSystem;
class GameLayer:public BaseLayer{
public:
	static cocos2d::CCScene* scene();
	GameBackground *gameBackground;
	cocos2d::CCTouch *touchPoint;
	MonsterSys *monsterSystem;
	FlyLamaSystem *flyLamaSystem;
	BirdSystem *birdSystem;
	int attackDragon;
	bool isPaused;
    float scale;
    void removeUseless();
	void clockBeforeStart(float);
	CREATE_FUNC(GameLayer);
	void dragonWin();
	void gameOverSceneSwitch();
	void lamaWin();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
	~GameLayer();
private:
	bool setUpdateViews();
	int clock_index;
    bool canTouch;
	cocos2d::CCSprite* tictac;
};
#endif