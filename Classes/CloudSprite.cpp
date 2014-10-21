#include "CloudSprite.h"
#include "GameBackground.h"
#include "RandNumber.h"
#include "BaseLayer.h"
USING_NS_CC;
CloudSprite::CloudSprite(void){
	speed = 1;
}
CloudSprite* CloudSprite::createWithType(int type){
	CCLOG("CloudSprite createWithType");
	CCTexture2D* cloud;
	CloudSprite* cs;
	switch(type){
	case 1://near
		cloud = CCTextureCache::sharedTextureCache()->textureForKey("gamebg/cloud_near_1.png");
		cs = (CloudSprite*)CloudSprite::createWithTexture(cloud);
		cs->setPositionY(19*BaseLayer::getWinSize().height/20);//-cs->getContentSize().height);
		cs->speed = 3.5;
		break;
	case 2: //near
		cloud = CCTextureCache::sharedTextureCache()->textureForKey("gamebg/cloud_near_2.png");
		cs = (CloudSprite*)CloudSprite::createWithTexture(cloud);
		cs->setPositionY(18*BaseLayer::getWinSize().height/20);
		cs->speed = 3;
		break;
	case 3: //mid
		cloud = CCTextureCache::sharedTextureCache()->textureForKey("gamebg/cloud_middle_1.png");
		cs = (CloudSprite*)CloudSprite::createWithTexture(cloud);
		cs->setPositionY(17*BaseLayer::getWinSize().height/20);
		cs->speed = 2.5;
		break;
	case 4: //mid
		cloud = CCTextureCache::sharedTextureCache()->textureForKey("gamebg/cloud_middle_2.png");
		cs = (CloudSprite*)CloudSprite::createWithTexture(cloud);
		cs->setPositionY(14*BaseLayer::getWinSize().height/20);
		cs->speed = 2;
		break;
	case 5: //back
		cloud = CCTextureCache::sharedTextureCache()->textureForKey("gamebg/cloud_far_1.png");
		cs = (CloudSprite*)CloudSprite::createWithTexture(cloud);
		cs->setPositionY(15*BaseLayer::getWinSize().height/20);
		cs->speed = 1.5;
		break;
	case 6: //back
		cloud = CCTextureCache::sharedTextureCache()->textureForKey("gamebg/cloud_far_2.png");
		cs = (CloudSprite*)CloudSprite::createWithTexture(cloud);
		cs->setPositionY(16*BaseLayer::getWinSize().height/20);
		cs->speed = 1;
		break;
	default:
		cloud = CCTextureCache::sharedTextureCache()->textureForKey("gamebg/cloud_middle_2.png");
		cs = (CloudSprite*)CloudSprite::createWithTexture(cloud);
		cs->setPositionY(BaseLayer::getWinSize().height-cs->getContentSize().height-65);
		break;
	}
	cs->setAnchorPoint(ccp(0,0));
	cs->setScale(0.5);
	/*cs->setScaleX((float)BaseLayer::getWinSize().width/cs->getContentSize().width);
	cs->setScaleY((float)BaseLayer::getWinSize().height/cs->getContentSize().height);*/
	cs->setPositionX(RandNumber::randFloat(0,BaseLayer::getWinSize().width-cs->getContentSize().width));
	//cs->setPosition(ccp(0,0));
	CCLOG("range %f",BaseLayer::getWinSize().width-cs->getContentSize().width);
	CCLOG("X = %f, Y = %f",cs->getPositionX(), cs->getPositionY());
	return cs;
}

bool CloudSprite::setUpdateView(){
	return true;
}


// Ö´ÐÐ±¼ÅÜ¶¯»­
void CloudSprite::runAnimation(){
	this->stopAllActions();
	this->schedule(schedule_selector(CloudSprite::moveRun),0.05f);
}

void CloudSprite::moveRun(float){
	float x=this->getPositionX();
	if( x > BaseLayer::getWinSize().width)
		x = -this->getContentSize().width * this->getScale();
	else
		x=x+this->speed;
	this->setPositionX(x);
}

void CloudSprite::setGameBackgroundUtils(GameBackground* gameBackground){
	this->gameBackground=gameBackground;
}

CloudSprite::~CloudSprite(void){

}