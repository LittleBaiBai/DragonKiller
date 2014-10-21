#include "GroundLamaSprite.h"
USING_NS_CC;
GroundLamaSprite::GroundLamaSprite(){
	CCLOG("new Lama");
    lamaScale = 0.5;
	up = 10;
	CCTexture2D *lamaHeads = CCTextureCache::sharedTextureCache()->textureForKey("game/lama_heads.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game/lama_heads.plist",lamaHeads);
	CCSpriteFrame* startFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("lama_head_4.png");
	this->lamaHead=CCSprite::createWithSpriteFrame(startFrame);
	lamaHead->setScale(lamaScale);
	lamaHead->setAnchorPoint(ccp(0,0.5));
	lamaHead->setPosition(ccp(getWinSize().width * 0.8,getWinSize().height * 0.11));

	CCTexture2D *lamasLegs = CCTextureCache::sharedTextureCache()->textureForKey("game/lama_legs.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game/lama_legs.plist",lamasLegs);
	startFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("lama_leg_4.png");
	this->lamaLeg=CCSprite::createWithSpriteFrame(startFrame);
	lamaLeg->setScale(lamaScale);
	lamaLeg->setAnchorPoint(ccp(0,0.5));
	lamaLeg->setPosition(ccp(getWinSize().width * 0.8,getWinSize().height * 0.11));
    
}
GroundLamaSprite::~GroundLamaSprite(){
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames(); 
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void GroundLamaSprite::setScale(float scale) {
    this->lamaScale = scale;
}

int GroundLamaSprite::isTouched(CCPoint target){
	float x = this->lamaHead->getPositionX();
	float y = this->lamaHead->getPositionY();
	float width = this->lamaHead->getContentSize().width*lamaScale;
	float halfHeight = this->lamaHead->getContentSize().height*lamaScale;
	if( target.x > x && target.x < x + width && target.y > y - halfHeight && target.y < y + halfHeight){
		return 1;
	}
	return 0;
}

GroundLamaSprite* GroundLamaSprite::CreateWithAnimation(){
	return NULL;
}


void GroundLamaSprite::RunAnimation(float positionX){
	runDistance = positionX;
//	CCLOG("_______bloodbar lama position___%f", positionX);
	CCActionInterval* moveTo1 = CCMoveTo::create(1, ccp(positionX - 20,lamaHead->getPositionY()));
	CCActionInterval* moveTo2 = CCMoveTo::create(1, ccp(positionX - 20,lamaHead->getPositionY()));
	this->lamaHead->runAction(moveTo1);
	this->lamaLeg->runAction(moveTo2);
}

void GroundLamaSprite::MoveAnimation(){
	//脖子伸缩动画
	headAnimFrames = CCArray::create();
	legAnimFrames = CCArray::create();

	for(int i=0;i<5;i++){
		this->headAnimFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("lama_head_%d.png",i+1)->getCString()));
	}
	for(int i=0;i<5;i++){
		this->headAnimFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("lama_head_%d.png",5-i)->getCString()));
	}
	for(int i=0; i<8; i++){
		this->legAnimFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("lama_leg_%d.png",i+1)->getCString()));
	}
	
	if(headAnimFrames->count()>0){
		CCAnimation *animation=CCAnimation::createWithSpriteFrames(headAnimFrames,0.2f);
		CCAnimate *animate=CCAnimate::create(animation);
		CCSequence* pse=CCSequence::create(animate,NULL);
		// 脖子伸缩
		this->lamaHead->runAction(CCRepeatForever::create(pse));
	}
	if(legAnimFrames->count()>0){
		CCAnimation *animation=CCAnimation::createWithSpriteFrames(legAnimFrames,0.1f);
		CCAnimate *animate=CCAnimate::create(animation);
		CCSequence* pse=CCSequence::create(animate,NULL);
		// 动腿
		this->lamaLeg->runAction(CCRepeatForever::create(pse));
	}

}



