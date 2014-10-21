#include "BloodBarSprite.h"
#include "BaseLayer.h"
USING_NS_CC;
BloodBarSprite::BloodBarSprite(){
	bool isRet=false;
	do 
	{
	float tex=BaseLayer::getWinCenter().x;
	float tey=BaseLayer::getWinCenter().y;
	
	// ��ӽ�����
	CCSprite* loadimg=CCSprite::create("loading/loading.png");
	CC_BREAK_IF(!loadimg);	
	this->create(loadimg);
	this->setType(kCCProgressTimerTypeBar);// ���óɺ����
	//���Կ����ǰ�������ʾЧ���Ľ���������
	this->setMidpoint(ccp(0,0)); 
	//  �����趨����������ǰ���ķ���������һ��Ǵ�������
	this->setBarChangeRate(ccp(1,0));
	this->setScaleX((float)BaseLayer::getWinSize().width/this->getContentSize().width);
	this->setScaleY((float)BaseLayer::getWinSize().height/this->getContentSize().height);
	this->setPosition(ccp(tex,tey));
	this->setPercentage(100);
	isRet=true;
	} while (0);
}
BloodBarSprite::~BloodBarSprite(){
}

void BloodBarSprite::setBloodPercentage(float percentChange){	
	if(percentChange == 0) return;
	this->bloodDirection = percentChange > 0 ? 1 : -1;
	stopAllActions();
	this->schedule(schedule_selector(BloodBarSprite::bloodBarMove),1/percentChange,(int)percentChange,0);
}

void BloodBarSprite::bloodBarMove(float){
	float x = this->getPercentage() + bloodDirection;
	this->setPercentage(x);
}