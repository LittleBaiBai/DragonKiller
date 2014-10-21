#ifndef __LOADING_WEL_LAYER_H__
#define __LOADING_WEL_LAYER_H__
#include "BaseLayer.h"
#include "EntryLayer.h"

class LoadingWelcomeLayer:public BaseLayer{
public:
	virtual bool init();
	CREATE_FUNC(LoadingWelcomeLayer);
	static cocos2d::CCScene* scene();
	void loadCallBack(cocos2d::CCObject* ped);// �첽����ͼƬʱ �Ļص�����
	LoadingWelcomeLayer();
private:
	int loadingNum;//������¼��ǰ�ļ���ͼƬ������
	int totalNum;// һ��Ҫ���ص�ͼƬ����
	bool setUpdateView();// ������ʼ��ҳ��� ����������
	void goWelcomeLayer();
};
#endif