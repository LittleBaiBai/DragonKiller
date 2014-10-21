#ifndef __GAME_WIN_LAYER_H__
#define __GAME_WIN_LAYER_H__
#include "cocos2d.h"
#include "BaseLayer.h"
#include "WelComeGameLayer.h"

class GameWinLayer : public BaseLayer{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(GameWinLayer);
	void menuReturnCallBack(cocos2d::CCObject* pSend); // ������ذ�ť �������¼�
private:
	bool setUpdateView();
};
#endif