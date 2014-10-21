#include "BirdClippingNode.h"

USING_NS_CC;

BirdClippingNode::BirdClippingNode(){
	//≥ı ºªØ≤√«–…Ë±∏
	//this->create();
	//≥ı ºªØ≤√«–ƒ£∞Â
	//Œ™«–∏Ó…Ë÷√≤√«–ƒ£∞Â
	birdTexture = CCTextureCache::sharedTextureCache()->textureForKey("game/bird_1.png");
//	startFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game/bird_1.png");
//	bird = CCSprite::createWithSpriteFrame(startFrame);
    bird = CCSprite::createWithTexture(birdTexture);
	birdScale = 0.5;
	
	birdHalfWidth = birdTexture->getContentSize().width*birdScale / 2;
	birdHalfHeight = birdTexture->getContentSize().height*birdScale / 2;
	xBirdMin = 0 + birdHalfWidth;
	xBirdMax = BaseLayer::getWinSize().width - birdHalfWidth;
	yBirdMin = 0 + birdHalfWidth * 2;
	yBirdMax = 2 * BaseLayer::getWinSize().height / 3 - birdHalfWidth;
	//CCLOG("Bird position range: %f, %f, %f, %f", xBirdMin, xBirdMax,yBirdMin, yBirdMax);
	
	bird->setScale(birdScale);
	/*if(RandNumber::randFloat0_1() > 0.5)
		bird->setPosition(ccp(RandNumber::randInt(-xBirdMin, -xBirdMax),RandNumber::randInt(yBirdMin, yBirdMax)));
	else*/
	bird->setPosition(ccp(BaseLayer::getWinSize().width + birdHalfWidth
		,RandNumber::randInt(yBirdMin, yBirdMax)));
	CCLOG("bird position x = %f, y = %f", bird->getPositionX(), bird->getPositionY());
	//this->addChild(bird);
    this->flyAnimation = CCAnimation::create();
	for(int i=0;i<3;i++){
		this->flyAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("game/bird_%d.png",i+1)->getCString());
	}
	for(int i=0;i<3;i++){
		this->flyAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("game/bird_%d.png",i+1)->getCString());
	}
    flyAnimation->setDelayPerUnit(0.1f);
	flyAnimation->setRestoreOriginalFrame(true);
}

void BirdClippingNode::birdStartActions(){
 //   CCLOG("IN BIRDSTARTACTION");
	CCAnimate *animate=CCAnimate::create(flyAnimation);
    CCRepeatForever* ccs = CCRepeatForever::create(animate);
    ccs->setTag(5);
	bird->runAction(ccs);
	//bird->runAction(animate);
   // birdWander(0);
    this->schedule(schedule_selector(BirdClippingNode::birdWander), 3.5, kCCRepeatForever, 0);
}

void BirdClippingNode::birdWander(float){
	/*ccBezierConfig tr;    
	float dx = RandNumber::randInt(xBirdMin, xBirdMax);
	float dy = RandNumber::randInt(yBirdMin, yBirdMax);
	float ctrlpt1x, ctrlpt1y, ctrlpt2x, ctrlpt2y;
	tr.endPosition=ccp(dx - bird->getPositionX(), dy - bird->getPositionY());
	ctrlpt1x = (dx - bird->getPositionX())/3;
	ctrlpt2x = (dx - bird->getPositionX())/3*2;
	ctrlpt1y = (dy - bird->getPositionY())/3;
	ctrlpt2y = (dy - bird->getPositionY())/3*2;
	tr.controlPoint_1=ccp(ctrlpt1x, ctrlpt1y);
	tr.controlPoint_2=ccp(ctrlpt2x, ctrlpt2y);
	
	CCActionInterval* bezierForward = CCBezierBy::create(5, tr);
	bezierForward->setTag(1);
	bird->runAction(bezierForward);*/
	float dx = RandNumber::randInt(xBirdMin, xBirdMax);
	float dy = RandNumber::randInt(yBirdMin, yBirdMax);
//	CCLOG("bird wander target x = %f, y = %f", dx, dy);
	CCActionInterval* moveTo = CCMoveTo::create(3.5, ccp(dx, dy));
	moveTo->setTag(1);
	bird->runAction(moveTo);
}

int BirdClippingNode::isAttacked(CCPoint target){
	float x = bird->getPositionX();
	float y = bird->getPositionY();
    
//	CCLOG("!!!!!!!!!!!!-------birdHalfWidth = %f, birdHalfHeight = %f---",birdHalfWidth, birdHalfHeight);
	if(target.x > x - birdHalfWidth && target.x < x + birdHalfWidth && target.y > y - birdHalfHeight && target.y < y + birdHalfHeight){
		CCLOG("BirdClippingNode:Bird got attacked! x = %f, y = %f", x, y);
//		CCSprite *holeStencilSprite = CCSprite::create("game/saliva_pool.png");
//		holeStencilSprite->setPosition(ccp(bird->getPositionX(),bird->getPositionY()));
//		holeStencilSprite->setScale(0.5f);
		//‘⁄ƒÒ…Ì…œÕ⁄∂¥
		//this->birdHolesStencil->addChild(holeStencilSprite);
		bird->stopActionByTag(1);
        this->unschedule(schedule_selector(BirdClippingNode::birdWander));
		bird->stopAllActions();
		CCTexture2D *deadBird = CCTextureCache::sharedTextureCache()->textureForKey("game/bird_dead.png");
		bird->setTexture(deadBird);
	//	bird->setScale(this->birdScale);
		return 1;
	}
	return 0;
}

int BirdClippingNode::resumeOneHole(CCPoint target){
	
//	this->bird->stopAllActions();
    this->unschedule(schedule_selector(BirdClippingNode::birdWander));
    this->bird->stopActionByTag(1);
	CCMoveTo* moveTo = CCMoveTo::create(4,target);
	CCFadeOut* fadeOut = CCFadeOut::create(3.f);
	CCScaleTo* scaleTo=CCScaleTo::create(3.f, 0);
    CCCallFunc* changePic = CCCallFunc::create(this,callfunc_selector(BirdClippingNode::wearCrown));
    CCSequence* ccs = CCSequence::create(moveTo, changePic, scaleTo, NULL);
    this->bird->runAction(ccs);
	
 //   this->bird->runAction(scaleTo);
	return 7;
}

void BirdClippingNode::wearCrown(){
    CCLOG("after move to bird at %f, %f", this->bird->getPositionX(), this->bird->getPositionY());
    this->bird->stopActionByTag(5);
    this->bird->setTexture(CCTextureCache::sharedTextureCache()->textureForKey("game/bird_hole_filler.png"));
    CCLOG("aaaaaaaaaaa!!!!!!!!after move to bird");
    
}
