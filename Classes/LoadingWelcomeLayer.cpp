#include "LoadingWelcomeLayer.h"
#include "WelComeGameLayer.h"
USING_NS_CC;
LoadingWelcomeLayer::LoadingWelcomeLayer(){
	this->loadingNum=0;
	this->totalNum=16;
}
bool LoadingWelcomeLayer::init(){
	bool isRet=false;
	do 
	{
        CC_BREAK_IF(!BaseLayer::init());
        CC_BREAK_IF(!this->setUpdateView());
        
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/gate_background.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/letou_cover.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/letou_rotate.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/start.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/start_press_1.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        //5
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/button_music_on.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/button_music_off.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/bubble_press_1.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/button_about.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/button_help.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        //10
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/button_more.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/bubble_left_down.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("gate/bubble_left_up.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("scene/tap_to_continue_1.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("game/about_cover.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        //15
        CCTextureCache::sharedTextureCache()->addImageAsync("game/about_content.png",this,callfuncO_selector(LoadingWelcomeLayer::loadCallBack));
        //16
        

	isRet=true;
	} while (0);
	return isRet;
}
CCScene* LoadingWelcomeLayer::scene(){
	CCScene* scene=CCScene::create();
	LoadingWelcomeLayer* layer=LoadingWelcomeLayer::create();
	scene->addChild(layer);
	return scene;
}
void LoadingWelcomeLayer::loadCallBack(CCObject* ped){
	loadingNum++;	 
    CCProgressTimer* pt=(CCProgressTimer*)this->getChildByTag(1);
	
	if(loadingNum<totalNum){
        CCLOG("========================== %d",loadingNum);
		float now=pt->getPercentage();
		pt->setPercentage(100/totalNum+now);
	}else{
		// �������ʱ����ת����Ӧ�Ľ���
		CCLOG("loading over");
		goWelcomeLayer();
	}
}


void LoadingWelcomeLayer::goWelcomeLayer(){
	CCScene* se=WelComeGameLayer::scene();
	CCLOG("start change scene in loadingwelcomeLayer");
	CCDirector::sharedDirector()->replaceScene(se);
}

bool LoadingWelcomeLayer::setUpdateView(){
	bool isRet=false;
	do
	{
        float tex=getWinCenter().x;
        float tey=getWinCenter().y;
        float scale;
        
        //// ���ý���������� ���ǰ����ŵ���Ļ�·���1/5��
        CCSprite* loadoutimg=CCSprite::create("loading/progressbar_cover.png");
        CC_BREAK_IF(!loadoutimg);
        scale = (float)BaseLayer::getWinSize().width/loadoutimg->getContentSize().width;
        loadoutimg->setScale(scale);
        loadoutimg->setPosition(ccp(tex,tey));
        this->addChild(loadoutimg,3);
        
        // ���ý������ı���ͼƬ ���ǰ����ŵ���Ļ�·���1/5��
        CCSprite* loadbackimg=CCSprite::create("loading/progressbar_background.png");
        CC_BREAK_IF(!loadbackimg);
        CCLOG("loading background %f", scale);
        loadbackimg->setScale(scale);
        loadbackimg->setPosition(ccp(tex,tey));
        this->addChild(loadbackimg,1);
        
        // ��ӽ�����
        CCSprite* loadimg=CCSprite::create("loading/progressbar_blood.png");
        CC_BREAK_IF(!loadimg);
        
        CCLOG("%f %f %f",BaseLayer::getWinSize().width,loadimg->getContentSize().width, scale );
        CCProgressTimer* pt = CCProgressTimer::create(loadimg);
        pt->setScale(scale);
        pt->setType(kCCProgressTimerTypeBar);// ���óɺ����
        //���Կ����ǰ�������ʾЧ���Ľ���������
        pt->setMidpoint(ccp(0,0));
        //  �����趨����������ǰ���ķ���������һ��Ǵ�������
        pt->setBarChangeRate(ccp(1,0));
        
        pt->setPosition(ccp(tex,tey));//+getWinSize().width*139/1080),tey));
        pt->setPercentage(0);
        this->addChild(pt,2,1);
        
        isRet=true;
	} while (0);
	return isRet;
}