#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__
#include "cocos2d.h"
#include "BaseLayer.h"
#include "GameLayer.h"
#include "WelComeGameLayer.h"


class PauseLayer : public BaseLayer{
public:
	cocos2d::CCSprite *eatingLama;
	void initEatingLama();
	static cocos2d::CCScene* scene();

	void menuBackCallback(CCObject* pSend);
	void menuRestartCallback(CCObject* pSend);
	void menuResumeCallback(CCObject* pSend);
	void waitForEating(float);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
	~PauseLayer();
	CREATE_FUNC(PauseLayer);
	bool setUpdateViews();
    
    float scale;
    //void setScale(float);
};
#endif