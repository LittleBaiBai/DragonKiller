#include "WelComeGameLayer.h"

USING_NS_CC;
//using namespace CocosDenshion;
bool WelComeGameLayer::init(){
	CCLOG("WelComeGameLayer");
    if(CCDirector::sharedDirector()->isPaused()){
        CCLOG("was paused!!!!");
        CCDirector::sharedDirector()->resume();
    }
    CCDirector::sharedDirector()->resume();
	bool isRet=false;
	do
	{
        CC_BREAK_IF(!BaseLayer::init());
        CC_BREAK_IF(!setUpdateView());
        CCLOG("here");
        isRet=true;
	} while (0);
	return isRet;
}

void WelComeGameLayer::onEnter(){
    CCLOG("WelcomeLayer on enter!!!");
	BaseLayer::onEnter();
//    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/dt.mp3",true);
//        if(CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()){
//    	}else {
//    		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isplay",true)){
//    			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/dt.mp3",true);
//     //°Ñ ÒôÀÖ×´Ì¬ÉèÖÃÎª²¥·Å×´Ì¬
//    			CCUserDefault::sharedUserDefault()->setBoolForKey("isplay",true);
//    		}
//    	}
}

CCScene* WelComeGameLayer::scene(){
	CCScene* scene=CCScene::create();
	WelComeGameLayer* layer=WelComeGameLayer::create();
	scene->addChild(layer);
	return scene;
}
bool WelComeGameLayer::setUpdateView(){
	bool isRet=false;
	do
	{
		CCLOG("WelComeGameLayer load background");
        //background
		CCSprite* pSpriteBg=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("gate/gate_background.png"));
        this->scaleX = (float)BaseLayer::getWinSize().width/(pSpriteBg->getContentSize().width);
        this->scaleY = (float)BaseLayer::getWinSize().height/(pSpriteBg->getContentSize().height);
		pSpriteBg->setScaleX(scaleX);
		pSpriteBg->setScaleY(scaleY);
        pSpriteBg->setPosition(getWinCenter());
		this->addChild(pSpriteBg,1);
        
        //rotating llama
		CCSprite* letou_rotate=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("gate/letou_rotate.png"));
		letou_rotate->setScaleX(scaleY);
		letou_rotate->setScaleY(scaleY);
        letou_rotate->setAnchorPoint(ccp(0.5,0.5));
        letou_rotate->setPosition(getWinCenter());
        CCSequence* pse=CCSequence::create(CCRotateBy::create(25.0f, 360),NULL);
        letou_rotate->runAction(CCRepeatForever::create(pse));
		this->addChild(letou_rotate,2);
        
        //cover on rotating llama
		CCSprite* letou_cover=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("gate/letou_cover.png"));
		letou_cover->setScaleX(scaleY);
		letou_cover->setScaleY(scaleY);
        letou_cover->setAnchorPoint(ccp(0.5,0.5));
		letou_cover->setPosition(getWinCenter());
		this->addChild(letou_cover,3);
        
        //bubbles
		CCSprite* bubble_up=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("gate/bubble_left_up.png"));
		bubble_up->setScaleX(scaleX);
		bubble_up->setScaleY(scaleY);
        bubble_up->setAnchorPoint(ccp(0,0));
		bubble_up->setPosition(ccp(0,0));
        CCMoveBy* cmb_1 = CCMoveBy::create(0.8f, ccp(-5, 5));
		CCSequence* bub1=CCSequence::create(cmb_1, cmb_1->reverse(), NULL);
        bubble_up->runAction(CCRepeatForever::create(bub1));
		this->addChild(bubble_up,3);
        
		CCSprite* bubble_down=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("gate/bubble_left_down.png"));
		bubble_down->setScaleX(scaleX);
		bubble_down->setScaleY(scaleY);
        bubble_down->setAnchorPoint(ccp(0,0));
		bubble_down->setPosition(ccp(0,0));
        CCMoveBy* cmb_2 = CCMoveBy::create(0.8f, ccp(5, 5));
        CCSequence* bub2=CCSequence::create(cmb_2, cmb_2->reverse(), NULL);
        bubble_down->runAction(CCRepeatForever::create(bub2));
		this->addChild(bubble_down,3);
        
		// åˆ›å»ºå¼€å§‹æ¸¸æˆ?èœå•æŒ‰é’® start
		start=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("gate/start.png"));
		start->setScaleX(scaleY);
		start->setScaleY(scaleY);
		CCSprite* start_selected=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("gate/start_press_1.png"));
		start_selected->setScaleX(scaleY);
		start_selected->setScaleY(scaleY);
        CCMenuItemSprite* pStart=CCMenuItemSprite::create(start, start_selected,this, menu_selector(WelComeGameLayer::menuStartCallback));
		pStart->setPosition(converSpritRel(getWinSize().width*0.63f,getWinSize().height*0.58f));
        
		// 添加声音菜单按钮 music
		CCTexture2D* textureon = CCTextureCache::sharedTextureCache()->textureForKey("gate/button_music_on.png");
		CCTexture2D* textureoff = CCTextureCache::sharedTextureCache()->textureForKey("gate/button_music_off.png");
        CCSprite* textureOn = CCSprite::createWithTexture(textureon);
        CCSprite* textureOff = CCSprite::createWithTexture(textureoff);
        textureOn->setScaleX(scaleY);
        textureOn->setScaleY(scaleY);
        textureOff->setScaleX(scaleY);
        textureOff->setScaleY(scaleY);
		CCMenuItemSprite* musicOn=CCMenuItemSprite::create(textureOn,CCSprite::createWithTexture(textureon));
		CC_BREAK_IF(!musicOn);
		CCMenuItemSprite* musicOff=CCMenuItemSprite::create(textureOff,CCSprite::createWithTexture(textureoff));
		CC_BREAK_IF(!musicOn);
		CCMenuItemToggle* pMusic=NULL;
		// å½“çŽ°åœ?éŸ³ä¹æ˜?æ’­æ”¾çš„æ—¶å€™ç•Œé¢ä¸Šæ˜¾ç¤ºçš„æŒ‰é’®åº”è¯¥æ˜¯ æš‚åœéŸ³ä¹æŒ‰é’® åä¹‹ åˆ™æ˜¾ç¤ºæ’­æ”¾æŒ‰é’?
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isplay",false)){
			pMusic=CCMenuItemToggle::createWithTarget(this,menu_selector(WelComeGameLayer::musicOnAndOffCallBack),musicOff,musicOn,NULL);
		}else {
			pMusic=CCMenuItemToggle::createWithTarget(this,menu_selector(WelComeGameLayer::musicOnAndOffCallBack),musicOn,musicOff,NULL);
		}
		CC_BREAK_IF(!pMusic);
		pMusic->setPosition(converSpritRel(getWinSize().width*0.90f,getWinSize().height*0.18f));
        
		// åˆ›å»ºæ³¡æ³¡ç¢?
		CCTexture2D* splash=CCTextureCache::sharedTextureCache()->textureForKey("gate/bubble_press_1.png");
        splash_ani = CCAnimation::create();
        splash_ani->addSpriteFrameWithFileName("gate/bubble_press_1.png");
        splash_ani->addSpriteFrameWithFileName("gate/bubble_press_2.png");
        splash_ani->addSpriteFrameWithFileName("gate/bubble_press_3.png");
        splash_ani->addSpriteFrameWithFileName("gate/bubble_press_4.png");
        splash_ani->addSpriteFrameWithFileName("gate/bubble_press_5.png");
        splash_ani->setRestoreOriginalFrame(true);
        splash_ani->setDelayPerUnit(0.1f);
        splash_ani->retain();
        
        //关于我们 菜单按钮
		CCTexture2D* aboutItem = CCTextureCache::sharedTextureCache()->textureForKey("gate/button_about.png");
        about = CCSprite::createWithTexture(aboutItem);
        CCSprite* splash_about = CCSprite::createWithTexture(splash);
        about->setScaleX(scaleY);
        about->setScaleY(scaleY);
        splash_about->setScaleX(scaleY * 1.1);
        splash_about->setScaleY(scaleY * 1.1);
		CCMenuItemSprite* pAbout=CCMenuItemSprite::create(about,splash_about,this,menu_selector(WelComeGameLayer::menuCoderCallback));
		CC_BREAK_IF(!pAbout);
		pAbout->setPosition(converSpritRel(getWinSize().width*1.0f,getWinSize().height*0.35f));

		//see entrance animation 菜单按钮
		CCTexture2D* questionItem = CCTextureCache::sharedTextureCache()->textureForKey("gate/button_help.png");
        question = CCSprite::createWithTexture(questionItem);
        CCSprite* splash_help = CCSprite::createWithTexture(splash);
        question->setScaleX(scaleY);
        question->setScaleY(scaleY);
        splash_help->setScaleX(scaleY / 1.22);
        splash_help->setScaleY(scaleY / 1.22);
		CCMenuItemSprite* pHelp=CCMenuItemSprite::create(question,splash_help,this,menu_selector(WelComeGameLayer::menuHelpCallback));
		CC_BREAK_IF(!pHelp);
		pHelp->setPosition(converSpritRel(getWinSize().width*0.25f,getWinSize().height*0.28f));
        
		//more? 菜单按钮
		CCTexture2D* moreItem = CCTextureCache::sharedTextureCache()->textureForKey("gate/button_more.png");
        more = CCSprite::createWithTexture(moreItem);
        CCSprite* splash_more = CCSprite::createWithTexture(splash);
        more->setScaleX(scaleY);
        more->setScaleY(scaleY);
        splash_more->setScaleX(scaleY);
        splash_more->setScaleY(scaleY);
		CCMenuItemSprite* pMore=CCMenuItemSprite::create(more,splash_more,this,menu_selector(WelComeGameLayer::menuMoreCallback));
		CC_BREAK_IF(!pMore);
		pMore->setPosition(converSpritRel(getWinSize().width*0.68f,getWinSize().height*0.15f));
		
        
		CCMenu* pMenu=CCMenu::create(pStart, pMusic, pAbout, pHelp, pMore, NULL);
		CC_BREAK_IF(!pMenu);
        
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu,5);
        
        
        
	    isRet=true;
	} while (0);
	return isRet;
}

void WelComeGameLayer::musicOnAndOffCallBack(CCObject* pSend){
    printf("********* music callback ");
	if(CCUserDefault::sharedUserDefault()->getBoolForKey("isplay",false)){
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CCLOG("music is stop");
		CCUserDefault::sharedUserDefault()->setBoolForKey("isplay",false);
	}else {
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		CCUserDefault::sharedUserDefault()->setBoolForKey("isplay",true);
		CCLOG("music is play");
	}
    
}

void WelComeGameLayer::menuStartCallback(CCObject* pSend){CCAnimation *animation=CCAnimation::create();
    printf("********* startcallback ");
	animation->addSpriteFrameWithFileName("gate/start_press_1.png");
	animation->addSpriteFrameWithFileName("gate/start_press_2.png");
	animation->addSpriteFrameWithFileName("gate/start_press_3.png");
	animation->addSpriteFrameWithFileName("gate/start_press_4.png");
	animation->addSpriteFrameWithFileName("gate/start_press_5.png");
    animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(0.15f);
    CCAnimate* animate = CCAnimate::create(animation);
    //	this->start->runAction(animate);
    CCSequence* ccs=CCSequence::create(animate, CCCallFunc::create(this,callfunc_selector(WelComeGameLayer::callStart)), NULL);
    this->start->runAction(ccs);
}

void WelComeGameLayer::callStart(){
    CCScene* se=LoadingGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5,se));
}

void WelComeGameLayer::menuCoderCallback(CCObject* pSend){
    printf("********* about callback ");
    CCSequence* ccs=CCSequence::create(CCAnimate::create(this->splash_ani), CCCallFunc::create(this,callfunc_selector(WelComeGameLayer::callCoder)), NULL);
	this->about->runAction(ccs);
}

void WelComeGameLayer::callCoder() {
    CCScene* se=AboutCoderLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5,se));
}

void WelComeGameLayer::menuHelpCallback(CCObject* pSend){
    printf("********* help callback ");
    CCSequence* ccs=CCSequence::create(CCAnimate::create(this->splash_ani), CCCallFunc::create(this,callfunc_selector(WelComeGameLayer::callHelp)), NULL);
	this->question->runAction(ccs);
}

void WelComeGameLayer::callHelp() {
	CCScene* se=LoadingEntryLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5,se));
}

void WelComeGameLayer::menuMoreCallback(CCObject* pSend){
    printf("********* more callback ");
    this->more->runAction(CCAnimate::create(this->splash_ani));
	//CCScene* se=MoreLayer::scene();
	//CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5,se));
}

void WelComeGameLayer::onExit(){
    CCLOG("Welcome layer on exit");
	BaseLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/tap_to_continue_1.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/tap_to_continue_2.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/tap_to_continue_3.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/tap_to_continue_4.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/gate_background.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/letou_cover.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/letou_rotate.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/start.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/start_press_1.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/button_music_on.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/button_music_off.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/bubble_press_1.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/button_about.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/button_help.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/button_more.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/bubble_left_down.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gate/bubble_left_up.png");
   
}

WelComeGameLayer::~WelComeGameLayer(){
	//CCTextureCache::removeTexture(<#cocos2d::CCTexture2D *texture#>);
}

