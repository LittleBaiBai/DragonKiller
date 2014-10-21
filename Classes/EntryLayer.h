#ifndef __ENTRY_LAYER_H__
#define __ENTRY_LAYER_H__
#include "BaseLayer.h"
#include "cocos2d.h"
#include "LoadingWelcomeLayer.h"
// 这个类是入场动画
class EntryLayer:public BaseLayer{
public:
	cocos2d::CCSprite * background;
	cocos2d::CCSprite * entry_I;
	cocos2d::CCSprite * entry_II;
	cocos2d::CCSprite * entry_III;
	cocos2d::CCSprite * entry_IV;
	cocos2d::CCSprite * entry_V;

	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(EntryLayer);
	void changeScene();
	void changeScene2(float);
	void changeToWelcome();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *ptouch, cocos2d::CCEvent *pevent);
	virtual void ccTouchMoved(cocos2d::CCTouch *ptouch, cocos2d::CCEvent *pevent);
	virtual void ccTouchEnded(cocos2d::CCTouch *ptouch, cocos2d::CCEvent *pevent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
	~EntryLayer();
private:
    float scaleX;
    float scaleY;
	bool setUpdateViews();
	int entry_index;
};
#endif