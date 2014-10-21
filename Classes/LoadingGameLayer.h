#ifndef __LOADING_GAME_LAYER_H__
#define __LOADING_GAME_LAYER_H__
#include "BaseLayer.h"
#include "GameLayer.h"

class LoadingGameLayer:public BaseLayer{
public:
	virtual bool init();
	CREATE_FUNC(LoadingGameLayer);
	static cocos2d::CCScene* scene();
	void loadCallBack(cocos2d::CCObject* ped);// �첽����ͼƬʱ �Ļص�����
	LoadingGameLayer();
private:
	int loadingNum;//������¼��ǰ�ļ���ͼƬ������
	int totalNum;// һ��Ҫ���ص�ͼƬ����
	bool setUpdateView();// ������ʼ��ҳ��� ����������
	void goGameLayer();
};
#endif