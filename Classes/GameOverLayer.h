#ifndef __GAME_OVER_LAYER_H__
#define __GAME_OVER_LAYER_H__
#include "cocos2d.h"
#include "BaseLayer.h"
#include "WelComeGameLayer.h"

class GameOverLayer : public BaseLayer{
public:
	int cantouch;
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(GameOverLayer);
	void tapToContinue();
	void stampLama();
    virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

private:
	bool setUpdateView();
};
#endif