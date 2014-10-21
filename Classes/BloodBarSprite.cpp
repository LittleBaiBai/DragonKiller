#include "BloodBarSprite.h"
#include "BaseLayer.h"
USING_NS_CC;
BloodBarSprite::BloodBarSprite(){
	bool isRet=false;
	do 
	{
	float tex=BaseLayer::getWinCenter().x;
	float tey=BaseLayer::getWinCenter().y;
	
	// 添加进度条
	CCSprite* loadimg=CCSprite::create("loading/loading.png");
	CC_BREAK_IF(!loadimg);	
	this->create(loadimg);
	this->setType(kCCProgressTimerTypeBar);// 设置成横向的
	//可以看作是按矩形显示效果的进度条类型
	this->setMidpoint(ccp(0,0)); 
	//  用来设定进度条横向前进的方向从左向右或是从右向左
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