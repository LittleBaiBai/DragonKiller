#include "MonsterSys.h"
USING_NS_CC;
MonsterSys::MonsterSys(){
}
MonsterSys::~MonsterSys(){}
void MonsterSys::initDragon(){
	//龙
	do{
	//龙的底色
	CCTexture2D* gameDragonBg = CCTextureCache::sharedTextureCache()->textureForKey("game/dragon_bg.png");
	dragonBg = CCSprite::createWithTexture(gameDragonBg);
	dragonBg->setAnchorPoint(ccp(0,0));
	dragonBg->setScaleX((float)BaseLayer::getWinSize().width/dragonBg->getContentSize().width);
	dragonBg->setScaleY((float)BaseLayer::getWinSize().height/dragonBg->getContentSize().height);
	this->gameLayer->addChild(dragonBg,2);
	//龙的身体
	CCTexture2D* gameDragon=CCTextureCache::sharedTextureCache()->textureForKey("game/dragon.png");
	dragonHoleArray = CCArray::create();
	dragonHoleArray->retain();
	dragon = CCSprite::createWithTexture(gameDragon);
	dragon->setScaleX((float)BaseLayer::getWinSize().width/dragon->getContentSize().width);
	dragon->setScaleY((float)BaseLayer::getWinSize().height/dragon->getContentSize().height);
	CC_BREAK_IF(!dragon);
	dragon->setPosition(BaseLayer::getWinCenter());
	dragonClipper= CCClippingNode::create();
    //显示切割后剩余部分
    dragonClipper->setInverted(true);
    //设置alpha阈值
    dragonClipper->setAlphaThreshold( 0.9f );
	//切割龙
	dragonClipper->addChild(dragon);
	//初始化裁切模板的集合
	dragonHolesStencil= CCNode::create();
    dragonHolesStencil->retain();
	//为切割设置裁切模板
    dragonClipper->setStencil( dragonHolesStencil);
	this->gameLayer->addChild(dragonClipper,2);

	//龙的眼睛
	/*CCTexture2D* gameDragonEyeBg = CCTextureCache::sharedTextureCache()->textureForKey("game/dragon_eye_opened.png");
	CCSprite* dragonEyeBg = CCSprite::createWithTexture(gameDragonEyeBg);
	dragonEyeBg->setAnchorPoint(ccp(0,0));
	dragonEyeBg->setScaleX((float)BaseLayer::getWinSize().width/dragonEyeBg->getContentSize().width);
	dragonEyeBg->setScaleY((float)BaseLayer::getWinSize().height/dragonEyeBg->getContentSize().height);
	this->gameLayer->addChild(dragonEyeBg,3);*/
	//龙的眼皮
	CCTexture2D* gameDragonEyeBow = CCTextureCache::sharedTextureCache()->textureForKey("game/dragon_eye_closed.png");
	CCSprite* dragonEyeBow = CCSprite::createWithTexture(gameDragonEyeBow);
	dragonEyeBow->setAnchorPoint(ccp(0,0));
	dragonEyeBow->setScaleX((float)BaseLayer::getWinSize().width/dragonEyeBow->getContentSize().width);
	dragonEyeBow->setScaleY((float)BaseLayer::getWinSize().height/dragonEyeBow->getContentSize().height);
	CCActionInterval *blink = CCBlink::create(1.f,1);
	this->gameLayer->addChild(dragonEyeBow,3);
	dragonEyeBow->runAction(CCRepeatForever::create(blink));

	/*dragonImage = new CCImage();
	dragonImage->initWithImageFile("game/temp.png",CCImage::kFmtPng);
	unsigned char* dragonData = dragonImage->getData();
	dragonPixels = (unsigned int *)dragonData;
	CCLOG("Image size : %d, %d", dragonImage->getWidth(), dragonImage->getHeight());
	ccColor4B c = {0, 0, 0, 0};*/
	//for( i = 0; i < dragonImage->getWidth(); i++){
	//	for(j = 0; j < dragonImage->getHeight(); i++){
	//		if(dragonPixels[i + j * dragonImage->getWidth()] != 0){
	//			c.r = dragonPixels[i + j * dragonImage->getWidth()] & 0xff;
	//			c.g = (dragonPixels[i + j * dragonImage->getWidth()] >> 8) & 0xff;
	//			c.b = (dragonPixels[i + j * dragonImage->getWidth()] >> 16) & 0xff;
	//			c.a = (dragonPixels[i + j * dragonImage->getWidth()] >> 24) & 0xff;        //这个值  就是透明度
	//			CCLOG("i = %d, j = %d, c = %d, r = %d, g = %d, b = %d, a = %d",i,j, dragonPixels[i + j * dragonImage->getWidth()],c.r,c.g,c.b,c.a);
	//		}
	//	}
	//}
	}while(0);

}

void MonsterSys::initBloodBar(){
	bool isRet=false;
	do 
	{
	float tex=BaseLayer::getWinCenter().x;
	float tey=BaseLayer::getWinSize().height/10;
	float scale;
	// 设置进度条的背景图片 
    CCSprite* loadbackimg=CCSprite::create("loading/progressbar_background.png");
	CC_BREAK_IF(!loadbackimg);	
	scale = (float)BaseLayer::getWinSize().width/loadbackimg->getContentSize().width * 0.8;
	CCLOG("loading background %f", scale);
	loadbackimg->setScale(scale);
	loadbackimg->setPosition(ccp(tex,tey));
	this->gameLayer->addChild(loadbackimg,1);

	// 设置进度条的外框 
    CCSprite* loadoutimg=CCSprite::create("loading/progressbar_cover.png");
	CC_BREAK_IF(!loadoutimg);	
	scale = (float)BaseLayer::getWinSize().width/loadoutimg->getContentSize().width * 0.8;
	loadoutimg->setScale(scale);
	loadoutimg->setPosition(ccp(tex,tey));
	this->gameLayer->addChild(loadoutimg,3);
	
	// 添加进度条
	CCSprite* loadimg=CCSprite::create("loading/progressbar_blood.png");
	CC_BREAK_IF(!loadimg);	
	
	scale = BaseLayer::getWinSize().width/loadimg->getContentSize().width*0.57;
	CCLOG("%f %f %f",BaseLayer::getWinSize().width,loadimg->getContentSize().width, scale);
	this->bloodBar = CCProgressTimer::create(loadimg);
	this->bloodBar->setScale(scale);
	this->bloodBar->setType(kCCProgressTimerTypeBar);// 设置成横向的
	//可以看作是按矩形显示效果的进度条类型
	this->bloodBar->setMidpoint(ccp(0,0)); 
	//  用来设定进度条横向前进的方向从左向右或是从右向左
	this->bloodBar->setBarChangeRate(ccp(1,0));
	bloodBar->setAnchorPoint(ccp(0,0.5));
	tex = BaseLayer::getWinSize().width / 4;
	bloodBar->setPosition(ccp(tex,tey));//+getWinSize().width*139/1080),tey));
	bloodBar->setPercentage(100);
	this->gameLayer->addChild(bloodBar,2);

	isRet=true;
	} while (0);
}

void MonsterSys::initGroundLama(){
	lama = new GroundLamaSprite();
	this->gameLayer->addChild(lama->lamaLeg,3);
	this->gameLayer->addChild(lama->lamaHead,3);
	lama->MoveAnimation();
}

void MonsterSys::setBloodPercentage(float percentage){
    if(this->bloodBar->getPercentage() > 100 || this->bloodBar->getPercentage() <= 20)
        return;
	CCLOG("<<<<<<<<<<<<<<<before change percentage = %f>>>>>>>>>>>>>>>>>", this->bloodBar->getPercentage());
	CCProgressFromTo* progressTo = CCProgressFromTo::create(1,this->bloodBar->getPercentage(),percentage);  
	this->lama->RunAnimation(percentage/100 * bloodBar->getContentSize().width * bloodBar->getScale()+ bloodBar->getPositionX());
	CCCallFunc *callFunc = CCCallFunc::create(this,callfunc_selector(MonsterSys::checkBloodBar));
	this->bloodBar->runAction(CCSequence::create(progressTo, callFunc, NULL));
	//this->scheduleOnce(schedule_selector(MonsterSys::checkBloodBar),1);	
}

void MonsterSys::checkBloodBar(){
//	CCLog("(((((((((((((((((((((percentage = %f__________________________",bloodBar->getPercentage());
//	if(this->bloodBar->getPercentage() <=37){
//		CCLOG("(((((((((((((((warning!!!!!!!!!!!!!!!!!!!");
//		this->gameLayer->gameBackground->showOverWarning();
//	}
//	else{
//		CCLOG(">>>>>>>>>>>>>>>Remove warning>>>>>>>>>>>>>>>>>>");
//		this->gameLayer->gameBackground->removeOverWarning();
//	}
//	if(this->bloodBar->getPercentage() <= 17){
//		this->gameLayer->dragonWin();
//	}
}

void MonsterSys::setGameLayer(GameLayer* GameLayer){
	this->gameLayer=GameLayer;
}

void MonsterSys::attackDragon(CCPoint attackPoint){
	CCLOG("attack dragon %f,%f",attackPoint.x,attackPoint.y);
	//ccColor4B c = {0, 0, 0, 0};
	//int i = (int)attackPoint.x / getWinSize().width * dragonImage->getWidth();
	//int j = (int)attackPoint.y / getWinSize().height * dragonImage->getHeight();
	//unsigned int * pixel = dragonPixels + j * dragonImage->getWidth() + i;  
	//c.r = *pixel & 0xff;
	//c.g = (*pixel >> 8) & 0xff;
	//c.b = (*pixel >> 16) & 0xff;
	//c.a = (*pixel >> 24) & 0xff;        //这个值  就是透明度
	//CCLOG("i = %d, j = %d, c = %d, r = %d, g = %d, b = %d, a = %d",i,j, *pixel,c.r,c.g,c.b,c.a);
	CCSprite *holeStencilSprite = CCSprite::create("game/saliva_pool.png");
	holeStencilSprite->setAnchorPoint(ccp(0.5,0.5));
	holeStencilSprite->setPosition(ccp(attackPoint.x,attackPoint.y));
	holeStencilSprite->setScale(0.5f);
	//在恐龙身上挖洞
	this->dragonHolesStencil->addChild(holeStencilSprite);
	dragonHoleArray->addObject(holeStencilSprite);
	//进度条修改
	this->setBloodPercentage(bloodBar->getPercentage()-5);
}
