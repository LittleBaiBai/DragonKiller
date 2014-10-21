#include "GameOverLayer.h"
USING_NS_CC;
CCScene* GameOverLayer::scene(){
	CCScene* scene=CCScene::create();
	GameOverLayer* layer=GameOverLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverLayer::init(){
	bool isRet=false;
	do 
	{
	cantouch = 0;
	setTouchEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -3, true);
	CC_BREAK_IF(!BaseLayer::init());
	CC_BREAK_IF(!setUpdateView());
	isRet=true;
	} while (0);
	return isRet;
}
bool GameOverLayer::setUpdateView(){
	bool isRet=false;
	do 
	{
   // Ìí¼Ó±³¾°Í¼Æ¬
	CCTexture2D* texture=CCTextureCache::sharedTextureCache()->textureForKey("gamebg/dragon_win_8.png");
	CCSprite* psbg=CCSprite::createWithTexture(texture);
	psbg->setScale(BaseLayer::getWinSize().width / texture->getContentSize().width);
	psbg->setAnchorPoint(ccp(0,0));
	CC_BREAK_IF(!psbg);
	this->addChild(psbg,1);

	CCTexture2D* word = CCTextureCache::sharedTextureCache()->textureForKey("gamebg/dragon_win.png");
	CCSprite* movingWord = CCSprite::createWithTexture(word);
	movingWord->setScale(0.7);
	movingWord->setPositionX(getWinSize().width + movingWord->getContentSize().width);
	movingWord->setPositionY(getWinCenter().y / 0.7);
	CCActionInterval* moveTo = CCMoveTo::create(1, ccp(getWinCenter().x/2, movingWord->getPositionY()));
	CCActionInterval* moveBack = CCMoveTo::create(0.2, ccp(getWinCenter().x, movingWord->getPositionY()));
	CCCallFunc *stampLama = CCCallFunc::create(this,callfunc_selector(GameOverLayer::stampLama));
	movingWord->runAction(CCSequence::create(moveTo, moveBack, stampLama, NULL));
	this->addChild(movingWord,2);
	isRet=true;
	} while (0);
	return isRet;
}

void GameOverLayer::stampLama(){
	CCTexture2D* stamp_pic = CCTextureCache::sharedTextureCache()->textureForKey("gamebg/game_over_stamp.png");
	CCSprite* stamp=CCSprite::createWithTexture(stamp_pic);
    stamp->setScale(1.5);
	this->addChild(stamp,4);
	CCCallFunc *tapToContinue = CCCallFunc::create(this,callfunc_selector(GameOverLayer::tapToContinue));
	CCActionInterval* moveTo = CCMoveTo::create(0.3,ccp(getWinCenter().x, getWinCenter().y * 8 / 9 ));
	CCActionInterval* scaleTo = CCScaleTo::create(0.3, 0.7);
	stamp->runAction(moveTo);
	stamp->runAction(CCSequence::create(scaleTo, tapToContinue, NULL));
}

void GameOverLayer::tapToContinue(){
	CCTextureCache::sharedTextureCache()->addImage("scene/tap_to_continue_1.png");
    CCTexture2D *continue_pic1 = CCTextureCache::sharedTextureCache()->textureForKey("scene/tap_to_continue_1.png");
	CCSprite* tapToContinue = CCSprite::createWithTexture(continue_pic1);
	tapToContinue->setAnchorPoint(ccp(0,0));
	tapToContinue->setScale(0.5);
	tapToContinue->setPositionX(tapToContinue->getContentSize().width * 0.3);
	CCAnimation *continueAnimation=CCAnimation::create();
	continueAnimation->addSpriteFrameWithFileName("scene/tap_to_continue_1.png");
	continueAnimation->addSpriteFrameWithFileName("scene/tap_to_continue_2.png");
	continueAnimation->addSpriteFrameWithFileName("scene/tap_to_continue_3.png");
	continueAnimation->addSpriteFrameWithFileName("scene/tap_to_continue_4.png");
	continueAnimation->setDelayPerUnit(0.5);
	continueAnimation->setRestoreOriginalFrame(true);
	CCAnimate *continueAnimate=CCAnimate::create(continueAnimation);
	tapToContinue->runAction(CCRepeatForever::create(continueAnimate));
	cantouch = 1;
	this->addChild(tapToContinue, 3);
}

void GameOverLayer::onExit(){
    CCLOG("Game Over Layer on exit");
	BaseLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
   // CCTextureCache::sharedTextureCache()->removeAllTextures();
    this->removeAllChildren();
//  this->release();
//    CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/warning_1.png"); // ÒªËÀÊ±µÄºì¹â
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/warning_2.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/warning_3.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/background.png"); // ÓÎÏ·±³¾°
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/cloud_near_1.png"); // ÓÎÏ·±³¾°
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/cloud_near_2.png"); // ¹­åóÎäÆ÷
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/cloud_middle_1.png"); //  ¹­¼ý×Óµ¯
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/cloud_middle_2.png"); // ÑªÌõ±³¾°
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/cloud_far_1.png"); //  ÑªÌõ
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/cloud_far_2.png"); //  ÑªÌõ
//	
//	//CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/back_bubble.png");//ºóÃæµÄÅÝÅÝ
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/front_bubble.png");//Ç°ÃæµÄÅÝÅÝ
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/dragon_shadow.png");//ÁúµÄÒõÓ°
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/decoration.png");//¶¥ÉÏµÄ×°ÊÎ
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/dragon_win.png");//dragon win×Ö
	CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/game_over_stamp.png");//²ÝÄàÂíµÄÕÂ
	//15
    
    CCTextureCache::sharedTextureCache()->removeTextureForKey("gamebg/dragon_win_8.png");
//	for (int i = 1; i <= 8; i++) {
//		CCTextureCache::sharedTextureCache()->removeTextureForKey(CCString::createWithFormat("gamebg/dragon_win_%d.png",i)->getCString());
//	}
//
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/dragon.png");//Áú
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/dragon_bg.png");//±³ºóµÄÁú
//	//25
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/lama_heads.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/lama_legs.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pilot/lama_blink.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pilot/lama_face.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pilot/lama_whole.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pilot/lama_saliva.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pilot/lama_saliva_short.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pilot/lama_spit.png");
//	//33
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/bird_1.png");
//    CCTextureCache::sharedTextureCache()->removeTextureForKey("game/bird_2.png");
//    CCTextureCache::sharedTextureCache()->removeTextureForKey("game/bird_3.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/bird_dead.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/bird_hole_filler.png");
//	
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/saliva_pool.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/dragon_eye_opened.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("game/dragon_eye_closed.png");
//	//39
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_1.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_2.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_3.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_4.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_5.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_eat_1.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_eat_2.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/bend_eat_3.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/button_resume.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/button_restart.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("pause/button_menu.png");
	//50
    CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/tap_to_continue_1.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/tap_to_continue_2.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/tap_to_continue_3.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/tap_to_continue_4.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/clock_1.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/clock_2.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/clock_3.png");
//	CCTextureCache::sharedTextureCache()->removeTextureForKey("scene/clock_0.png");
	
}

bool GameOverLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	CCLOG("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Over");
	if(cantouch == 1){
		CCScene* scene=LoadingWelcomeLayer::scene();
		CCDirector::sharedDirector()->replaceScene(scene);
	}
	return false;
}