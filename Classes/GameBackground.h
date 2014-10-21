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
	cocos2d::CCArray* getCloudArray();// 返回背景云数组
	void showClouds(int count);	//显示云
	void showOverWarning();
	void removeOverWarning();
	void setGameLayer(GameLayer* GameLayer);
	void productClouds();
	void releaseClouds();
	void setBackground();

private:
	cocos2d::CCArray* cloudsArray;// 保存背景云
	GameLayer* gameLayer;// 游戏主类
	
//	void addGameLayer(CloudSprite *cloudSprite);// 把云添加到主界面里面

};
#endif