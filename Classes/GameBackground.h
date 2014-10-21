#ifndef __GAME_BACKGROUND_H__
#define __GAME_BACKGROUND_H__
#include "cocos2d.h"
#include "CloudSprite.h"
class GameLayer;
class GameBackground{
public:
	cocos2d::CCSprite* warning;

	GameBackground();
	~GameBackground();
	cocos2d::CCArray* getCloudArray();// ���ر���������
	void showClouds(int count);	//��ʾ��
	void showOverWarning();
	void removeOverWarning();
	void setGameLayer(GameLayer* GameLayer);
	void productClouds();
	void releaseClouds();
	void setBackground();

private:
	cocos2d::CCArray* cloudsArray;// ���汳����
	GameLayer* gameLayer;// ��Ϸ����
	
//	void addGameLayer(CloudSprite *cloudSprite);// ������ӵ�����������

};
#endif