#ifndef __LOADING_ENTRY_LAYER_H__
#define __LOADING_ENTRY_LAYER_H__
#include "BaseLayer.h"
#include "EntryLayer.h"
#include "LoadingWelcomeLayer.h"

class LoadingEntryLayer:public BaseLayer{
public:
	virtual bool init();
	CREATE_FUNC(LoadingEntryLayer);
	static cocos2d::CCScene* scene();
	void loadCallBack(cocos2d::CCObject* ped);// �첽����ͼƬʱ �Ļص�����
	LoadingEntryLayer();
private:
	int loadingNum;//������¼��ǰ�ļ���ͼƬ������
	int totalNum;// һ��Ҫ���ص�ͼƬ����
	bool setUpdateView();// ������ʼ��ҳ��� ����������
	void goEntryLayer();
};
#endif