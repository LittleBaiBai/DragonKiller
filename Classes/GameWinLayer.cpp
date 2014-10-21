#include "GameWinLayer.h"
USING_NS_CC;
CCScene* GameWinLayer::scene(){
	CCScene* scene=CCScene::create();
	GameWinLayer* layer=GameWinLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GameWinLayer::init(){
	bool isRet=false;
	do 
	{
	CC_BREAK_IF(!BaseLayer::init());
	CC_BREAK_IF(!setUpdateView());
	isRet=true;
	} while (0);
	return isRet;
}
bool GameWinLayer::setUpdateView(){
	bool isRet=false;
	do 
	{
   // 添加背景图片
	CCTexture2D* textture=CCTextureCache::sharedTextureCache()->textureForKey("welcome/coder.png");
	CCSprite* psbg=CCSprite::createWithTexture(textture);
	CC_BREAK_IF(!psbg);
	psbg->setPosition(converSpritRel(getWinSize().width/2,getWinSize().height/2));
	this->addChild(psbg,1);

	// 创建返回菜单
	CCTexture2D* texturestar_up = CCTextureCache::sharedTextureCache()->textureForKey("welcome/return_up.png");
	CCTexture2D* texturestar_down = CCTextureCache::sharedTextureCache()->textureForKey("welcome/return_down.png");
	CCMenuItemSprite* pStar=CCMenuItemSprite::create(CCSprite::createWithTexture(texturestar_up),CCSprite::createWithTexture(texturestar_down),this,menu_selector(GameWinLayer::menuReturnCallBack));
	CC_BREAK_IF(!pStar);
	CCLOG("here");
	pStar->setAnchorPoint(ccp(1,0));
	pStar->setPosition(converSpritRel(getWinSize().width,10));
	CCMenu* pMenu=CCMenu::create(pStar,NULL);
	CC_BREAK_IF(!pMenu);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,2);
	isRet=true;
	} while (0);
	return isRet;
}


void GameWinLayer::menuReturnCallBack(CCObject* pSend){
	CCScene* scene=WelComeGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(1,scene));
}