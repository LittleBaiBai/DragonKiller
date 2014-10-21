#include "PauseLayer.h"
USING_NS_CC;

CCScene* PauseLayer::scene(){
	CCScene* scene=CCScene::create();
	PauseLayer* layer=PauseLayer::create();
	scene->addChild(layer);
	return scene;
}

bool PauseLayer::init(){
	bool isRet=false;
	do 
	{
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!setUpdateViews());
		isRet = true;
	} while (0);
	return isRet;
}
//
//void PauseLayer::setScale(float scale) {
//    this->scale = scale;
//}

bool PauseLayer::setUpdateViews(){
	initEatingLama();
	
	// 创建返回菜单
	CCTexture2D* textureMenu = CCTextureCache::sharedTextureCache()->textureForKey("pause/button_menu.png");
	CCTexture2D* textureMenuDown = CCTextureCache::sharedTextureCache()->textureForKey("pause/button_menu.png");
	CCMenuItemSprite* pBackMenu=CCMenuItemSprite::create(CCSprite::createWithTexture(textureMenu),CCSprite::createWithTexture(textureMenuDown),this,menu_selector(PauseLayer::menuBackCallback));
	pBackMenu->setScale(0.5f);
	pBackMenu->setPosition(converSpritRel(getWinSize().width*0.53f,getWinSize().height*0.77f));

	// 创建重新开始
	CCTexture2D* textureRestart = CCTextureCache::sharedTextureCache()->textureForKey("pause/button_restart.png");
	CCTexture2D* textureRestartDown = CCTextureCache::sharedTextureCache()->textureForKey("pause/button_restart.png");
	CCMenuItemSprite* pRestart=CCMenuItemSprite::create(CCSprite::createWithTexture(textureRestart),CCSprite::createWithTexture(textureRestart),this,menu_selector(PauseLayer::menuRestartCallback));
	pRestart->setScale(0.5f);
	pRestart->setPosition(converSpritRel(getWinSize().width*0.3f,getWinSize().height*0.7f));

	// 创建resume
	CCTexture2D* textureResume = CCTextureCache::sharedTextureCache()->textureForKey("pause/button_resume.png");
	CCTexture2D* textureResumeDown = CCTextureCache::sharedTextureCache()->textureForKey("pause/button_resume.png");
	CCMenuItemSprite* pResume=CCMenuItemSprite::create(CCSprite::createWithTexture(textureResume),CCSprite::createWithTexture(textureResumeDown),this,menu_selector(PauseLayer::menuResumeCallback));
	pResume->setScale(0.5f);
	pResume->setPosition(converSpritRel(getWinSize().width*0.73f,getWinSize().height*0.65f));
	
	CCMenu* pMenu=CCMenu::create(pBackMenu,pRestart,pResume,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,2);

	return true;
}
void PauseLayer::initEatingLama(){
	eatingLama = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("pause/bend_5.png"));
	//eatingLama->setAnchorPoint(ccp(0,0));
    eatingLama->setPosition(getWinCenter());
	eatingLama->setScaleX(getWinSize().width / eatingLama->getContentSize().width);
	eatingLama->setScaleY(getWinSize().height / eatingLama->getContentSize().height);
	this->addChild(eatingLama);
	CCRect c = CCRectMake(0,0,getWinSize().width,getWinSize().height);
	CCAnimation *bendAnimation=CCAnimation::create();
	//bendAnimation->addSpriteFrameWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("pause/bend_1.png"),c);
	//bendAnimation->addSpriteFrameWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("pause/bend_2.png"),c);
	//bendAnimation->addSpriteFrameWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("pause/bend_3.png"),c);
	//bendAnimation->addSpriteFrameWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("pause/bend_4.png"),c);
	//bendAnimation->addSpriteFrameWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("pause/bend_5.png"),c);
	//bendAnimation->addSpriteFrameWithFileName("pause/bend_1.png");
	bendAnimation->addSpriteFrameWithFileName("pause/bend_1.png");
	bendAnimation->addSpriteFrameWithFileName("pause/bend_2.png");
	bendAnimation->addSpriteFrameWithFileName("pause/bend_3.png");
	bendAnimation->addSpriteFrameWithFileName("pause/bend_4.png");
	bendAnimation->addSpriteFrameWithFileName("pause/bend_5.png");
	bendAnimation->setDelayPerUnit(0.2f);
	bendAnimation->setRestoreOriginalFrame(true);
	CCAnimate *bendAnimate=CCAnimate::create(bendAnimation);
	eatingLama->runAction(bendAnimate);
	this->scheduleOnce(schedule_selector(PauseLayer::waitForEating),1);
	//eatingLama->runAction(CCSequence::createWithTwoActions(bendAnimate,eatAnimate));
}

void PauseLayer::waitForEating(float){
	CCAnimation *eatAnimation=CCAnimation::create();
	eatAnimation->addSpriteFrameWithFileName("pause/bend_eat_1.png");
	eatAnimation->addSpriteFrameWithFileName("pause/bend_eat_2.png");
	eatAnimation->addSpriteFrameWithFileName("pause/bend_eat_3.png");
	eatAnimation->setDelayPerUnit(0.3f);
	eatAnimation->setRestoreOriginalFrame(true);
	CCAnimate *eatAnimate=CCAnimate::create(eatAnimation);
	eatingLama->runAction(CCRepeatForever::create(eatAnimate));
}

void PauseLayer::menuBackCallback(CCObject* pSend){
    this->removeAllChildren();
    //this->removeAllComponents();
    
	CCScene* se=LoadingWelcomeLayer::scene();
	CCLOG("pressed on menu");
	CCDirector::sharedDirector()->replaceScene(se);
  //  this->release();
    
	//CCTextureCache::sharedTextureCache()->removeAllTextures();
}

void PauseLayer::menuRestartCallback(CCObject* pSend){
	CCLOG("pressed on Restart");
    
//	CCScene* se=LoadingGameLayer::scene();
//	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(1,se));
    CCScene* se = GameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(se);
}

void PauseLayer::menuResumeCallback(CCObject* pSend){
	CCLOG("pressed on Resume");
	CCDirector::sharedDirector()->popScene();
	
}

void PauseLayer::onEnter(){
	BaseLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(  
		this,//在那个类中实现触屏回调函数  
		0, //优先级  
		true);//触摸时间是否被该目标截获  
}
bool PauseLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	return false;
}


void PauseLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	
}
void PauseLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){

}
void PauseLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	
}

void PauseLayer::onExit()
{
	BaseLayer::onExit();
	CCLOG("PauseLayerExit!!");
    
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

PauseLayer::~PauseLayer(){
}