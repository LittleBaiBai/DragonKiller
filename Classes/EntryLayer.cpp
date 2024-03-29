#include "EntryLayer.h"

USING_NS_CC;
CCScene* EntryLayer::scene(){
	CCScene* scene=CCScene::create();
	EntryLayer* layer = EntryLayer::create();
	scene->addChild(layer);
	return scene;
}
bool EntryLayer::init(){
	bool isRet=false;
	do 
	{
		this->entry_index = 1;
        //	setTouchEnabled(true);
        //	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
        CCTextureCache::sharedTextureCache()->addImage("scene/tap_to_continue_1.png");
		CCTexture2D *continue_pic1 = CCTextureCache::sharedTextureCache()->textureForKey("scene/tap_to_continue_1.png");
        CCSprite* tapToContinue = CCSprite::createWithTexture(continue_pic1);
        tapToContinue->setAnchorPoint(ccp(0,0));
        tapToContinue->setScale(0.5);
        tapToContinue->setPositionX(tapToContinue->getContentSize().width*0.7);
        CCAnimation *continueAnimation=CCAnimation::create();
        continueAnimation->addSpriteFrameWithFileName("scene/tap_to_continue_1.png");
        continueAnimation->addSpriteFrameWithFileName("scene/tap_to_continue_2.png");
        continueAnimation->addSpriteFrameWithFileName("scene/tap_to_continue_3.png");
        continueAnimation->addSpriteFrameWithFileName("scene/tap_to_continue_4.png");
        continueAnimation->setDelayPerUnit(1);
        continueAnimation->setRestoreOriginalFrame(true);
        CCAnimate *continueAnimate=CCAnimate::create(continueAnimation);
        tapToContinue->runAction(CCRepeatForever::create(continueAnimate));
        this->addChild(tapToContinue, 100);
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!setUpdateViews());
		isRet=true;
	} while (0);
	return isRet;
}
bool EntryLayer::setUpdateViews(){
	CCLOG("EntryLayer setUpdateViews() %d", entry_index);
	//tap to continue
	
	//³¡¾°Ò»
	if (entry_index == 1) {
		background = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("entry1/entry1_background.png"));
        this->scaleX = BaseLayer::getWinSize().width / background->getContentSize().width;
        this->scaleY =BaseLayer::getWinSize().height / background->getContentSize().height;
		background->setScaleX(scaleX);
		background->setScaleY(scaleY);
		background->setAnchorPoint(ccp(0, 0));
		background->setPosition(ccp(0, 0));
		this->addChild(background, 1);
		entry_I = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("entry1/entry1_bigletou.png"));
		entry_I->setScaleX(scaleX);
		entry_I->setScaleY(scaleY);
		entry_I->setPosition(ccp(90,40));
		this->addChild(entry_I, 2);
		CCRotateTo *crt = CCRotateTo::create(2.5, 55);	//²ÎÊýÖ¸3Ãë×ª90¶È
		CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(EntryLayer::changeScene));
		CCSequence* pse=CCSequence::create(crt, callFunc, NULL);
		this->entry_I->runAction(pse);
	}
	else if (entry_index == 2) {
		background->setTexture(CCTextureCache::sharedTextureCache()->textureForKey("entry2/entry_2.png"));
		this->scheduleOnce(schedule_selector(EntryLayer::changeScene2), 2);
	}
	else if (entry_index == 3) {
		background->setTexture(CCTextureCache::sharedTextureCache()->textureForKey("entry3/entry_3_1.png"));
		CCAnimation *animation=CCAnimation::create();
		for (int i = 1; i <= 15; i++) {
			animation->addSpriteFrameWithFileName(CCString::createWithFormat("entry3/entry_3_%d.png",i)->getCString());
		}
		for (int i = 0 ; i < 10; i++){
			animation->addSpriteFrameWithFileName("entry3/entry_3_15.png");
		}
		animation->setDelayPerUnit(0.15f);
		animation->setRestoreOriginalFrame(true);
		CCAnimate *animate=CCAnimate::create(animation);
		CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(EntryLayer::changeScene));
		CCSequence* pse=CCSequence::create(animate, callFunc, NULL);
		this->background->runAction(pse);
	}
	else if (entry_index == 4) {
		CCAnimation *animation=CCAnimation::create();
		for (int i = 1; i <= 25; i++) {
			animation->addSpriteFrameWithFileName(CCString::createWithFormat("entry4/entry_4_%d.png",i)->getCString());
		}
		for (int i = 0; i < 3 ; i ++){
			animation->addSpriteFrameWithFileName("entry4/entry_4_25.png");
		}
		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);
		CCAnimate *animate=CCAnimate::create(animation);
		CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(EntryLayer::changeScene));
		CCSequence* pse=CCSequence::create(animate, callFunc, NULL);
		this->background->runAction(pse);
	}
	else if (entry_index == 5) {	//ÎÞÍ¼
		CCAnimation *animation=CCAnimation::create();
		for (int i = 1; i <= 16; i++) {
			animation->addSpriteFrameWithFileName(CCString::createWithFormat("entry5/entry_5_%d.png",i)->getCString());
		}
		for (int i = 0; i < 3 ; i ++){
			animation->addSpriteFrameWithFileName("entry5/entry_5_16.png");
		}
		animation->setDelayPerUnit(0.18f);
		animation->setRestoreOriginalFrame(true);
		CCAnimate *animate=CCAnimate::create(animation);
		CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(EntryLayer::changeScene));
		CCSequence* pse=CCSequence::create(animate, callFunc, NULL);
		this->background->runAction(pse);
	}
	else {
		CCLOG("here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		background->setTexture(CCTextureCache::sharedTextureCache()->textureForKey("entry6/entry_6.png"));
		this->scheduleOnce(schedule_selector(EntryLayer::changeScene2), 3);
	}
	return true;
}

void EntryLayer::changeScene() {
	if (entry_index == 1) {
		this->removeChild(entry_I);
	}
	if (entry_index == 6) {
		CCScene* se = LoadingWelcomeLayer::scene();
		CCLOG("start change scene");
		CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5,se));
	}
	CCLOG("EntryLayer before changeScene: %d", this->entry_index);
	this->entry_index++;
	setUpdateViews();
}

void EntryLayer::changeScene2(float) {
	if (entry_index == 6) {
		CCScene* se = LoadingWelcomeLayer::scene();
		CCLOG("start change scene");
		CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5,se));
	}
	this->entry_index++;
	setUpdateViews();
}

void EntryLayer::changeToWelcome(){
	CCScene* se = LoadingWelcomeLayer::scene();
	CCLOG("start change scene");
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5,se));
}

void EntryLayer::onEnter(){
	BaseLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(  
		this,//ÔÚÄÇ¸öÀàÖÐÊµÏÖ´¥ÆÁ»Øµ÷º¯Êý  
		0, //ÓÅÏÈ¼¶  
		true);//´¥ÃþÊ±¼äÊÇ·ñ±»¸ÃÄ¿±ê½Ø»ñ  
}

void EntryLayer::onExit(){
	BaseLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/tap_to_continue_1.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/tap_to_continue_2.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/tap_to_continue_3.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/tap_to_continue_4.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("entry1/entry1_background.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("entry1/entry1_bigletou.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("entry2/entry_2.png");
	//54
	for (int i = 1; i <= 15; i++) {
		CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("entry3/entry_3_%d.png",i)->getCString());
	}

	for (int i = 1; i <= 25; i++) {
		CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("entry4/entry_4_%d.png",i)->getCString());
	}
    
	for (int i = 1; i <= 16; i++) {
		CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("entry5/entry_5_%d.png",i)->getCString());
	}
	CCTextureCache::sharedTextureCache()->removeTextureForKey("entry6/entry_6.png");
}

bool EntryLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	changeToWelcome();
	return false;
}

void EntryLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){

}
void EntryLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){

}
void EntryLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){

} 

EntryLayer::~EntryLayer(){
}