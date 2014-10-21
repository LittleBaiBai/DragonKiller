#include "GameLayer.h"

USING_NS_CC;
CCScene* GameLayer::scene(){
	CCScene* scene=CCScene::create();
	GameLayer* layer=GameLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GameLayer::init(){
	bool isRet=false;
	do 
	{
        scale = 0.4;
		setTouchEnabled(true);
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, true);
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!setUpdateViews());
		isRet=true;
		this->clock_index = 3;
	} while (0);
	return isRet;
}
bool GameLayer::setUpdateViews(){
	bool isRet=false;
	isPaused = false; //ø™ º ±‘›Õ£◊¥Ã¨Œ™∑Ò
	do 
	{
	//≥ı ºªØ±≥æ∞
	CCLOG("GameLayer setUpdateView");
	this->gameBackground = new GameBackground();
	gameBackground->setGameLayer(this);
	gameBackground->setBackground();
	gameBackground->productClouds();
	gameBackground->showClouds(6);
	//CCLOG("monstersys init");
	////≥ı ºªØπ÷ŒÔ£¨ƒÒ∫Õ—™≤€
	this->monsterSystem = new MonsterSys();
        monsterSystem->setGameLayer(this);
	monsterSystem->initDragon();
	monsterSystem->initBloodBar();
	monsterSystem->initGroundLama();

	////≥ı ºªØ≤›ƒ‡¬Ì
	this->flyLamaSystem = new FlyLamaSystem();
	flyLamaSystem->setGameLayer(this);
	flyLamaSystem->produceLamas(3);
	flyLamaSystem->showLamas(3);

	//≥ı ºªØƒÒœµÕ≥
	this->birdSystem = new BirdSystem();
	this->addChild(birdSystem);
	birdSystem->setGameLayer(this);
	birdSystem->showBirds();
	//µπº∆ ±ø™ º
	tictac = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("scene/clock_3.png"));
	tictac->setScaleX(BaseLayer::getWinSize().width / tictac->getContentSize().width);
	//CCLOG("@@@@@@@@@@@@@@@@@@@@2 ")
	tictac->setScaleY(BaseLayer::getWinSize().height / tictac->getContentSize().height);
	tictac->setAnchorPoint(ccp(0, 0));
	tictac->setPosition(ccp(0, 0));
	this->clock_index = 2;
	this->addChild(tictac, 100);
	this->schedule(schedule_selector(GameLayer::clockBeforeStart), 1, 4, 0);

	isRet=true;
	} while (0);
	return isRet;
}


void GameLayer::clockBeforeStart(float) {
	CCLOG("@@@@@@@@@@@@@@@@@@@@ clock_index = %d @@@@@@@@@@@@@@@@@@@@2", clock_index);
	if (clock_index < 0) {
		CCLOG("@@@@@@@@@@@remove child@@@@@@@@@@@@@@2");
		this->removeChild(tictac);
		return;
	}
	tictac->setTexture(CCTextureCache::sharedTextureCache()->textureForKey(CCString::createWithFormat("scene/clock_%d.png",clock_index--)->getCString()));
}
void GameLayer::onEnter(){
	BaseLayer::onEnter();
    canTouch = true;
}
bool GameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	touchPoint = pTouch;
	touchPoint->retain();
    if (canTouch == false) return false;
	if(this->monsterSystem->lama->isTouched(ccp(pTouch->getLocation().x,pTouch->getLocation().y)) == 1){
		CCLOG("^^^^^^^^^^^^Touched on ground lama^^^^^^^^^^^");
		if(this->isPaused == true){
			this->isPaused = false;
		}
		else{
			CCDirector::sharedDirector()->pushScene(PauseLayer::scene());
			this->isPaused = true;
		}
	}
	else
		flyLamaSystem->TouchToSpit(pTouch->getLocation());
	return false;
}

void GameLayer::onExit(){
	BaseLayer::onExit();
    canTouch=false;
	CCLOG("GameLayerExit********************GameLayerExit");
//	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void GameLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	
}
void GameLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){

}
void GameLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	
}

void GameLayer::removeUseless() {
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/warning_1.png"); // “™À¿ ±µƒ∫Ïπ‚
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/warning_2.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/warning_3.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/background.png"); // ”Œœ∑±≥æ∞
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/cloud_near_1.png"); // ”Œœ∑±≥æ∞
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/cloud_near_2.png"); // π≠ÂÛŒ‰∆˜
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/cloud_middle_1.png"); //  π≠º˝◊”µØ
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/cloud_middle_2.png"); // —™Ãı±≥æ∞
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/cloud_far_1.png"); //  —™Ãı
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/cloud_far_2.png"); //  —™Ãı
	
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/back_bubble.png");//∫Û√Êµƒ≈›≈›
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/front_bubble.png");//«∞√Êµƒ≈›≈›
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/dragon_shadow.png");//¡˙µƒ“ı”∞
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/decoration.png");//∂•…œµƒ◊∞ Œ
	//15
    
	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/dragon.png");//¡˙
	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/dragon_bg.png");//±≥∫Ûµƒ¡˙
	//25
	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/lama_heads.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/lama_legs.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pilot/lama_blink.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pilot/lama_face.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pilot/lama_whole.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pilot/lama_saliva.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pilot/lama_saliva_short.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pilot/lama_spit.png");
	//33
	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/bird_1.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("game/bird_2.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("game/bird_3.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/bird_dead.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("game/bird_hole_filler.png");
	
	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/saliva_pool.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/dragon_eye_opened.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/dragon_eye_closed.png");
	//38
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_1.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_2.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_3.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_4.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_5.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_eat_1.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_eat_2.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_eat_3.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/button_resume.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/button_restart.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/button_menu.png");
	//49
	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/clock_1.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/clock_2.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/clock_3.png");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/clock_0.png");
    
    this->removeAllChildren();
}

void GameLayer::dragonWin(){
	CCTexture2D *over_pic1 = CCTextureCache::sharedTextureCache()->textureForKey("gamebg/dragon_win_8.png");
	CCSprite* over = CCSprite::createWithTexture(over_pic1);
	over->setAnchorPoint(ccp(0,0));
	over->setScaleX(BaseLayer::getWinSize().width / over_pic1->getContentSize().width);
	over->setScaleY(BaseLayer::getWinSize().height / over_pic1->getContentSize().height);
//	CCAnimation *overAnimation=CCAnimation::create();
//	for(int i = 1; i <= 8; i++)
//		overAnimation->addSpriteFrameWithFileName(CCString::createWithFormat("gamebg/dragon_win_%d.png",i)->getCString());
//	overAnimation->setRestoreOriginalFrame(true);
//	overAnimation->setDelayPerUnit(0.15f);
//	overAnimation->setRestoreOriginalFrame(true);
//	CCAnimate *overAnimate=CCAnimate::create(overAnimation);
	this->addChild(over, 11);
	//CCCallFunc *callFunc = CCCallFunc::create(this,callfunc_selector(GameLayer::gameOverSceneSwitch));
	//over->runAction(CCSequence::create(overAnimate, callFunc, NULL));
    gameOverSceneSwitch();
    
}

void GameLayer::gameOverSceneSwitch(){
	CCScene* se=GameOverLayer::scene();
	CCLOG("start change scene to game over");
	CCDirector::sharedDirector()->replaceScene(se);
    removeUseless();
}

void GameLayer::lamaWin(){
    removeUseless();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

GameLayer::~GameLayer(){
	CCLOG("~~~~~~~~~~~~~~~~~~~~~GameLayer~~~~~~~~~~~~~~~~~~~~~~~");
}