#ifndef __MONSTER_SPRITE_H__
#define __MONSTER_SPRITE_H__
#include "cocos2d.h"
#include "GameBackground.h"
#include "BaseLayer.h"
class GameBackground;
class CloudSprite:public cocos2d::CCSprite{
public:
	CloudSprite(void);
	~CloudSprite(void);
	int type;
	float speed;
	void moveRun(float tie);// 移动函数
	static CloudSprite* createWithType(int type);
	void runAnimation();// 执行奔跑动画
	// 第一个参数的意思是 加载的plist 文件的名字 第二个是 plist 对应的图片纹理 第三个是 图片的通用名字 第四个 走路动画图片张数，第五个是 攻击时候的参数  第六个是 死亡动画的张数
	// 在这里贴别说明一点为了达到动画的通用性 我们规定 plist 中的图片命名格式是这样的 pic-1编号 是跑步图片 pic-2编号是 攻击图片 pic-x编号是死亡图片
	//static CloudSprite* createWithMonsterRul(const char* filename,cocos2d::CCTexture2D* ccTexture2D,const char* pic,int runcount,int attackcount,int deathcout );
	void setGameBackgroundUtils(GameBackground* gameBackground);
protected:
	//virtual void runAnimationCallBack(cocos2d::CCNode* pSed);//奔跑动画回调函数
	virtual bool setUpdateView();
	GameBackground* gameBackground; 
//	void myload(float tim);
};
#endif