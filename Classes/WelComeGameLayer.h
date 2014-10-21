#ifndef __WELCOMEGAME_LAYER_H__
#define __WELCOMEGAME_LAYER_H__
#include "BaseLayer.h"
#include "AboutCoderLayer.h"
#include "LoadingGameLayer.h"
#include "LoadingEntryLayer.h"
//#include "SimpleAudioEngine.h"

class WelComeGameLayer:public BaseLayer{
public:
	static cocos2d::CCScene* scene();
    cocos2d::CCSprite* start;
    cocos2d::CCSprite* question;
    cocos2d::CCSprite* more;
    cocos2d::CCSprite* about;
	virtual bool init();
	CREATE_FUNC(WelComeGameLayer);
	virtual void onEnter();
	virtual void onExit();
    void callSchedule(float);
    void callCoder();
    void callStart();
    void callHelp();
private:
	// sÉèÖÃ½çÃæ
    float scaleX;
    float scaleY;
    cocos2d::CCAnimation* splash_ani;
	bool setUpdateView();
    void playItemSelect(cocos2d::CCObject* sender);
	// ²¥·Å»òÕßÔÝÍ£ÒôÀÖ»Øµ÷º¯Êý
	void musicOnAndOffCallBack(cocos2d::CCObject* pSend);
	// ¿ªÊ¼ÓÎÏ·»Øµ÷º¯Êý
	void menuStartCallback(cocos2d::CCObject* pSend);
	// Ìø×ªµÄ ¹ØÓÚ¿ª·¢Õß½çÃæµÄ»Øµ÷º¯Êý
	void menuCoderCallback(cocos2d::CCObject* pSend);
	void menuHelpCallback(cocos2d::CCObject* pSend);
	void menuMoreCallback(cocos2d::CCObject* pSend);
    ~WelComeGameLayer();
};
#endif