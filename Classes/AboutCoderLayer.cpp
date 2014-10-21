#include "AboutCoderLayer.h"
USING_NS_CC;
CCScene* AboutCoderLayer::scene(){
	CCScene* scene=CCScene::create();
	AboutCoderLayer* layer=AboutCoderLayer::create();
	scene->addChild(layer);
	return scene;
}

bool AboutCoderLayer::init(){
	bool isRet=false;
	do
	{
        setTouchEnabled(true);
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -2, true);
//        CCTextureCache::sharedTextureCache()->addImage("scene/tap_to_continue_1.png");
//        CCTexture2D *continue_pic1 = CCTextureCache::sharedTextureCache()->textureForKey("scene/tap_to_continue_1.png");
//        CCSprite* tapToContinue = CCSprite::createWithTexture(continue_pic1);
//        tapToContinue->setAnchorPoint(ccp(0,0));
//        tapToContinue->setScale(0.5);
//        tapToContinue->setPositionX(tapToContinue->getContentSize().width * 0.3);
//        CCAnimation *continueAnimation=CCAnimation::create();
//        continueAnimation->addSpriteFrameWithFileName("scene/tap_to_continue_1.png");
//        continueAnimation->addSpriteFrameWithFileName("scene/tap_to_continue_2.png");
//        continueAnimation->addSpriteFrameWithFileName("scene/tap_to_continue_3.png");
//        continueAnimation->addSpriteFrameWithFileName("scene/tap_to_continue_4.png");
//        continueAnimation->setDelayPerUnit(1);
//        continueAnimation->setRestoreOriginalFrame(true);
//        CCAnimate *continueAnimate=CCAnimate::create(continueAnimation);
//        tapToContinue->runAction(CCRepeatForever::create(continueAnimate));
//        this->addChild(tapToContinue, 100);
        CC_BREAK_IF(!BaseLayer::init());
        CC_BREAK_IF(!setUpdateView());
        isRet=true;
	} while (0);
	return isRet;
}

bool AboutCoderLayer::setUpdateView(){
	bool isRet=false;
    // 添加背景图片
	CCTexture2D* texture=CCTextureCache::sharedTextureCache()->textureForKey("game/about_cover.png");
	CCSprite* psbg=CCSprite::createWithTexture(texture);
    this->scaleX = (float)BaseLayer::getWinSize().width/(texture->getContentSize().width);
    this->scaleY = (float)BaseLayer::getWinSize().height/(texture->getContentSize().height);
    psbg->setScaleX(scaleX);
    psbg->setScaleY(scaleY);
    psbg->setPosition(getWinCenter());
	this->addChild(psbg,2);
    
	// 创建返回菜单
	CCTexture2D* words = CCTextureCache::sharedTextureCache()->textureForKey("game/about_content.png");
	CCSprite* moving=CCSprite::createWithTexture(words);
    moving->setScaleX(scaleX);
    moving->setScaleY(scaleY);
	moving->setAnchorPoint(ccp(0,1));
	moving->setPosition(converSpritRel(0, getWinSize().height));
    CCMoveTo* stay = CCMoveTo::create(2.f, moving->getPosition());
    CCMoveBy* move = CCMoveBy::create(8.0f, ccp(0, BaseLayer::getWinSize().height * 1222/1920));
    moving->runAction(CCSequence::create(stay, move, NULL));
	this->addChild(moving,1);
    
	isRet=true;
	return isRet;
}

bool AboutCoderLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    //CCLOG("!@$!@#%^#$^ Touch");
    CCScene* se=LoadingWelcomeLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5,se));
    return false;
}

void AboutCoderLayer::onExit() {

	BaseLayer::onExit();
	CCLOG("AboutLayerExit!!!!");
    this->removeAllChildren();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}