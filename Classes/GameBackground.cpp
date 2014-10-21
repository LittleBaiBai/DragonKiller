#include "GameBackground.h"
#include "GameLayer.h"
#include "CloudSprite.h"
USING_NS_CC;
GameBackground::GameBackground(){
	do{
	cloudsArray= CCArray::create();// 用来保存云
	cloudsArray->retain();
	}while(0);
}

void GameBackground::setBackground(){
	// 设置背景图片
	do{
	//背景图片
		CCLOG("0");
	CCTexture2D* gameBg=CCTextureCache::sharedTextureCache()->textureForKey("gamebg/background.png");
	CCSprite* pGameBg=CCSprite::createWithTexture(gameBg);
	pGameBg->setScaleX((float)BaseLayer::getWinSize().width/pGameBg->getContentSize().width);
        pGameBg->setScaleY((float)BaseLayer::getWinSize().height/pGameBg->getContentSize().height);
        this->gameLayer->scale =(float)BaseLayer::getWinSize().height/pGameBg->getContentSize().height;
	CC_BREAK_IF(!pGameBg);
	pGameBg->setPosition(BaseLayer::getWinCenter());
	gameLayer->addChild(pGameBg,1);
	//设置顶上的装饰
	CCTexture2D* gameDecoration=CCTextureCache::sharedTextureCache()->textureForKey("gamebg/decoration.png");
	CCSprite* pGameDecoration=CCSprite::createWithTexture(gameDecoration);
	pGameDecoration->setScaleX((float)BaseLayer::getWinSize().width/pGameBg->getContentSize().width);
	pGameDecoration->setScaleY((float)BaseLayer::getWinSize().height/pGameBg->getContentSize().height);
	CC_BREAK_IF(!pGameDecoration);
	pGameDecoration->setPosition(BaseLayer::getWinCenter());
	gameLayer->addChild(pGameDecoration,5);
	//龙的阴影
	CCTexture2D* gameDragonShadow=CCTextureCache::sharedTextureCache()->textureForKey("gamebg/dragon_shadow.png");
	CCSprite* pGameDragonShadow=CCSprite::createWithTexture(gameDragonShadow);
	pGameDragonShadow->setScaleX((float)BaseLayer::getWinSize().width/pGameDragonShadow->getContentSize().width);
	pGameDragonShadow->setScaleY((float)BaseLayer::getWinSize().height/pGameDragonShadow->getContentSize().height);
	CC_BREAK_IF(!pGameBg);
	pGameDragonShadow->setPosition(BaseLayer::getWinCenter());
	gameLayer->addChild(pGameDragonShadow,1);
	//前面的泡泡
	CCTexture2D* gameFrontBubble=CCTextureCache::sharedTextureCache()->textureForKey("gamebg/front_bubble.png");
	CCSprite* pGameFrontBubble=CCSprite::createWithTexture(gameFrontBubble);
	pGameFrontBubble->setScaleX((float)BaseLayer::getWinSize().width/pGameFrontBubble->getContentSize().width);
	pGameFrontBubble->setScaleY((float)BaseLayer::getWinSize().height/pGameFrontBubble->getContentSize().height);
	CC_BREAK_IF(!pGameFrontBubble);
	pGameFrontBubble->setPosition(BaseLayer::getWinCenter());
	gameLayer->addChild(pGameFrontBubble,3);
	//warning = null
	warning = NULL;
	
	}while(0);
}


void GameBackground::setGameLayer(GameLayer* GameLayer){
	this->gameLayer=GameLayer;
}

void GameBackground::productClouds(){		//根据云的位置产生云
	CCLOG("GameBackground product cloud before %d",getCloudArray()->count());
	getCloudArray()->addObject(CloudSprite::createWithType(6));
	getCloudArray()->addObject(CloudSprite::createWithType(5));
	getCloudArray()->addObject(CloudSprite::createWithType(4));
	getCloudArray()->addObject(CloudSprite::createWithType(3));
	getCloudArray()->addObject(CloudSprite::createWithType(2));
	getCloudArray()->addObject(CloudSprite::createWithType(1));
	CCLOG("GameBackground product cloud after %d",getCloudArray()->count());
		
}

void GameBackground::showClouds(int count){
	count = count < getCloudArray()->count() ? count : getCloudArray()->count();
	for( int i = 0; i < count; i++ ){
		CCLOG("GameBackground %d total %d",i,getCloudArray()->count());
		CloudSprite* cs=(CloudSprite*)this->getCloudArray()->objectAtIndex(i);
	//	cs->setPosition(ccp(0,0));
		CCLOG("in background X = %f, Y = %f",cs->getPositionX(), cs->getPositionY());
		if(this->gameLayer){
			this->gameLayer->addChild(cs,1);
			cs->runAnimation();
		}
	}
}

void GameBackground::releaseClouds(){
	GameBackground::showClouds(1);
}

CCArray* GameBackground::getCloudArray(){
	return this->cloudsArray;
}

void GameBackground::showOverWarning(){
    if(gameLayer->getChildByTag(10) != NULL)
        return;
    CCLOG("warning!!!!!");
	CCTexture2D *warning_pic1 = CCTextureCache::sharedTextureCache()->textureForKey("gamebg/warning_1.png");
	warning = CCSprite::createWithTexture(warning_pic1);
	warning->setAnchorPoint(ccp(0,0));
	warning->setScaleX(BaseLayer::getWinSize().width / warning_pic1->getContentSize().width);
	warning->setScaleY(BaseLayer::getWinSize().height / warning_pic1->getContentSize().height);
	CCAnimation *warningAnimation=CCAnimation::create();
	warningAnimation->addSpriteFrameWithFileName("gamebg/warning_1.png");
	warningAnimation->addSpriteFrameWithFileName("gamebg/warning_2.png");
	warningAnimation->addSpriteFrameWithFileName("gamebg/warning_3.png");
	warningAnimation->addSpriteFrameWithFileName("gamebg/warning_2.png");
	warningAnimation->setDelayPerUnit(0.15f);
	warningAnimation->setRestoreOriginalFrame(true);
	CCAnimate *warningAnimate=CCAnimate::create(warningAnimation);
	warning->runAction(CCRepeatForever::create(warningAnimate));
	
	gameLayer->addChild(warning, 8, 10);
}

void GameBackground::removeOverWarning(){
	if(gameLayer->getChildByTag(10) != NULL){
		CCLOG(">>>>>>>>>>>>>>>>>>>>>in bg to remove>>>>>>>>>>>");
		gameLayer->removeChild(warning);
	}
}

GameBackground::~GameBackground(){
	if (cloudsArray)
	{
		this->cloudsArray->autorelease();
	}
}