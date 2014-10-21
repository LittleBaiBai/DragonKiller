#include "FlyLamaSprite.h"

USING_NS_CC;
FlyLamaSprite::FlyLamaSprite(GameLayer* gameLayer){
	CCLOG("new FlyLama");
	this->gameLayer = gameLayer;
	this->lamaBody = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("pilot/lama_whole.png"));
	this->lamaSaliva = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("pilot/lama_saliva_short.png"));
	this->lamaFace = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("pilot/lama_face.png"));
	//初始化边界和缩放比例
    this->scale = this->gameLayer->scale;
	//scale = (float)BaseLayer::getWinSize().width/(lamaBody->getContentSize().width / 297 * 1080);
	speed = 80;
	this->totalTime = 0;
	xMin = 0;
	xMax = BaseLayer::getWinSize().width - scale * lamaBody->getContentSize().width;
	yMin = 2 * BaseLayer::getWinSize().height / 3;
	yMax = BaseLayer::getWinSize().height - scale* lamaBody->getContentSize().height;
	mouthToLeft = 60 * scale;
	mouthToDown = 190 * scale;
	this->readyToAttack = false;
	//初始化精灵位置
	lamaBody->setScale(scale);
	lamaBody->setAnchorPoint(ccp(0,0));
	float x = RandNumber::randInt(xMin, xMax);
	float y = RandNumber::randInt(yMin, yMax);
	lamaBody->setPosition(ccp(x, y));
	lamaFace->setScale(scale);
	lamaFace->setAnchorPoint(ccp(0,0));
	lamaFace->setPosition(ccp(-400,-600));
	lamaSaliva->setScale(scale);
	lamaSaliva->setAnchorPoint(ccp(0,0));
	lamaSaliva->setPosition(ccp(-400,-600));
	
}
FlyLamaSprite::~FlyLamaSprite(){
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames(); 
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void FlyLamaSprite::startMove() {
	CCLOG("---------------startmove--------------------");
	this->lamaBody->stopAllActions();
	this->BlinkAnimation();
	this->schedule(schedule_selector(FlyLamaSprite::WanderAnimation), 5, kCCRepeatForever, 0);
}

void FlyLamaSprite::WanderAnimation(float){
	this->readyToAttack = true;
	float dx = RandNumber::randInt(xMin, xMax);
	float dy = RandNumber::randInt(yMin, yMax);
	CCActionInterval* moveTo = CCMoveTo::create(5, ccp(dx, dy));
	this->lamaBody->runAction(moveTo);
}

void FlyLamaSprite::BlinkAnimation(){
	//眨眼动画
	CCAnimation *animation=CCAnimation::create();
	animation->addSpriteFrameWithFileName("pilot/lama_blink.png");
	animation->addSpriteFrameWithFileName("pilot/lama_whole.png");
	animation->setDelayPerUnit(0.3f);
	animation->setRestoreOriginalFrame(true);
	CCAnimate *animate=CCAnimate::create(animation);
	CCSequence* pse=CCSequence::create(animate,NULL);
	this->lamaBody->runAction(CCRepeatForever::create(pse));
}

void FlyLamaSprite::Spit(CCPoint target) {
	CCLOG("---------------Spit--------------------");
	this->readyToAttack = false;
	this->targetX = target.x - 34 * scale;
	this->targetY = target.y - 50 * scale;
	//停掉当前动画
	this->setVisible(true);
	this->lamaBody->stopAllActions();
	this->unschedule(schedule_selector(FlyLamaSprite::WanderAnimation));	
	//飞向目的地上方	
	float dist = targetX - mouthToLeft - lamaBody->getPositionX();
	totalTime = (dist>0?dist:-1*dist) / speed;
 //   CCLOG("^^^^^^^^^^^^^^^^^^^^^^^^total time before: %f, dist = %f", totalTime, dist);
	CCActionInterval * move = CCMoveTo::create(totalTime, ccp(targetX - mouthToLeft, lamaBody->getPositionY()));
	//Attack
	CCCallFunc *callFunc = CCCallFunc::create(this,callfunc_selector(FlyLamaSprite::Attack));
	CCSequence* pse=CCSequence::create(move, callFunc, NULL);
	this->lamaBody->runAction(pse);
}

void FlyLamaSprite::Attack() {
	CCLOG("------------------Attack------------------------");
	this->lamaBody->setTexture(CCTextureCache::sharedTextureCache()->textureForKey("pilot/lama_spit.png"));
	this->lamaSaliva->setPosition(ccp(lamaBody->getPositionX() + mouthToLeft, lamaBody->getPositionY() + mouthToDown));
	this->lamaSaliva->setVisible(true);
	this->lamaFace->setPosition(ccp(lamaBody->getPositionX(), lamaBody->getPositionY()));
	this->lamaFace->setVisible(true);
	//口水出现
	CCFadeIn* fadeIn = CCFadeIn::create(0.1f);
	this->lamaSaliva->setTexture(CCTextureCache::sharedTextureCache()->textureForKey("pilot/lama_saliva_short.png"));
	//口水换图
	this->scheduleOnce(schedule_selector(FlyLamaSprite::ChangeSaliva),2.5);
	//口水下落
	float distY = lamaBody->getPositionY() + mouthToDown - targetY;
    float t = sqrt(2 * distY / 9.8) / 2;
	totalTime += t;
   // CCLOG("^^^^^^^^^^^^^^^^^^^^^^^^total time after: %f, dist = %f", totalTime, distY);
	CCActionInterval * move = CCMoveTo::create(t, ccp(targetX,targetY));
	CCActionInterval * easeExponentialIn = CCEaseExponentialIn::create(move);
	//口水消失
	CCFadeOut* fade = CCFadeOut::create(0.1f);
	//切割龙	
	this->scheduleOnce(schedule_selector(FlyLamaSprite::startCuttingBird),t+0.1f);
	//CCLOG("@@@@@@@@@@@@@cut@@@@@@@@@@@@@@@@2");

	//下落后消失
	CCSequence* pse=CCSequence::create(fadeIn, easeExponentialIn, fade, NULL);
	this->lamaSaliva->runAction(pse);

	//恢复飞翔
	this->scheduleOnce(schedule_selector(FlyLamaSprite::CloseMouth),4);
	this->schedule(schedule_selector(FlyLamaSprite::WanderAnimation), 5, kCCRepeatForever, 8);
}

void FlyLamaSprite::startCuttingDragon(){
//	CCLOG("######################here");
	this->gameLayer->monsterSystem->attackDragon(ccp(targetX, targetY));
}

void FlyLamaSprite::startCuttingBird(float){
	if(this->gameLayer->birdSystem->attackBird(ccp(targetX, targetY)) == 0){
		startCuttingDragon();
	}
}

void FlyLamaSprite::ChangeSaliva(float) {
	this->lamaSaliva->setTexture(CCTextureCache::sharedTextureCache()->textureForKey("pilot/lama_saliva.png"));
}

void FlyLamaSprite::CloseMouth(float) {
	this->lamaBody->setTexture(CCTextureCache::sharedTextureCache()->textureForKey("pilot/lama_whole.png"));
	this->lamaFace->setVisible(false);
	this->BlinkAnimation();

	CCMoveBy* move = CCMoveBy::create(0.05f, ccp(-3, 0));
	this->lamaBody->runAction(move);
	CCMoveBy* verse = CCMoveBy::create(0.1f, ccp(6, 0));
	CCSequence* pse = CCSequence::create(verse, verse->reverse(), NULL);
	CCRepeat* rpt = CCRepeat::create(pse, 20);
	this->lamaBody->runAction(rpt); 
}

float FlyLamaSprite::getHorizontalDist(float targetX) {
	float dist = lamaBody->getPositionX() - mouthToLeft - targetX;
	return dist>0?dist:-1*dist;
}