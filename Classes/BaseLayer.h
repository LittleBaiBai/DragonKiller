#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__
#include "cocos2d.h"
#define	PI 3.14
class BaseLayer:public cocos2d::CCLayer{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(BaseLayer);
	static cocos2d::CCSize getWinSize();// �õ���ǰ���Ӵ��ڵĴ�С
	static cocos2d::CCPoint getWinOrigin();// �õ���ǰ���Ӵ��ڵ���ʼ��
	static cocos2d::CCPoint getWinCenter();// �õ���Ļ���м�ĵ�
	static cocos2d::CCPoint converSpritRel(float x, float y);//��������Ļ�е�λ��ת���� ���Ӵ��ڵ� λ��  
    
};
#endif