#ifndef __ABOUTCODER_LAYER_H__
#define __ABOUTCODER_LAYER_H__
#include "BaseLayer.h"
#include "WelComeGameLayer.h"
//  ���������  ���ڿ����߽���
class AboutCoderLayer:public BaseLayer{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(AboutCoderLayer);
	void menuReturnCallBack(cocos2d::CCObject* pSend); // ������ذ�ť �������¼�
    virtual void onExit();
private:
    float scaleX;
    float scaleY;
	bool setUpdateView();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};
#endif