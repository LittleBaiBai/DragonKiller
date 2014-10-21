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
	void moveRun(float tie);// �ƶ�����
	static CloudSprite* createWithType(int type);
	void runAnimation();// ִ�б��ܶ���
	// ��һ����������˼�� ���ص�plist �ļ������� �ڶ����� plist ��Ӧ��ͼƬ���� �������� ͼƬ��ͨ������ ���ĸ� ��·����ͼƬ������������� ����ʱ��Ĳ���  �������� ��������������
	// ����������˵��һ��Ϊ�˴ﵽ������ͨ���� ���ǹ涨 plist �е�ͼƬ������ʽ�������� pic-1��� ���ܲ�ͼƬ pic-2����� ����ͼƬ pic-x���������ͼƬ
	//static CloudSprite* createWithMonsterRul(const char* filename,cocos2d::CCTexture2D* ccTexture2D,const char* pic,int runcount,int attackcount,int deathcout );
	void setGameBackgroundUtils(GameBackground* gameBackground);
protected:
	//virtual void runAnimationCallBack(cocos2d::CCNode* pSed);//���ܶ����ص�����
	virtual bool setUpdateView();
	GameBackground* gameBackground; 
//	void myload(float tim);
};
#endif