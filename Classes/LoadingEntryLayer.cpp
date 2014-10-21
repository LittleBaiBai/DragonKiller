#include "LoadingEntryLayer.h"
USING_NS_CC;
LoadingEntryLayer::LoadingEntryLayer(){
	this->loadingNum=0;
	this->totalNum=61;
}
bool LoadingEntryLayer::init(){
	bool isRet=false;
	do 
	{
        CC_BREAK_IF(!BaseLayer::init());
        CC_BREAK_IF(!this->setUpdateView());
        
        CCTextureCache::sharedTextureCache()->addImageAsync("scene/tap_to_continue_1.png",this,callfuncO_selector(LoadingEntryLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("entry1/entry1_background.png",this,callfuncO_selector(LoadingEntryLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("entry1/entry1_bigletou.png",this,callfuncO_selector(LoadingEntryLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("entry2/entry_2.png",this,callfuncO_selector(LoadingEntryLayer::loadCallBack));
        //4
        for (int i = 1; i <= 15; i++) {
            CCTextureCache::sharedTextureCache()->addImageAsync(CCString::createWithFormat("entry3/entry_3_%d.png",i)->getCString(),this,callfuncO_selector(LoadingEntryLayer::loadCallBack));
        }
        //19
        for (int i = 1; i <= 25; i++) {
            CCTextureCache::sharedTextureCache()->addImageAsync(CCString::createWithFormat("entry4/entry_4_%d.png",i)->getCString(),this,callfuncO_selector(LoadingEntryLayer::loadCallBack));
        }
        //44
        for (int i = 1; i <= 16; i++) {
            CCTextureCache::sharedTextureCache()->addImageAsync(CCString::createWithFormat("entry5/entry_5_%d.png",i)->getCString(),this,callfuncO_selector(LoadingEntryLayer::loadCallBack));
        }
        //60
        CCTextureCache::sharedTextureCache()->addImageAsync("entry6/entry_6.png",this,callfuncO_selector(LoadingEntryLayer::loadCallBack));
        
        //61
        isRet=true;
	} while (0);
	return isRet;
}
CCScene* LoadingEntryLayer::scene(){
	CCScene* scene=CCScene::create();
	LoadingEntryLayer* layer=LoadingEntryLayer::create();
	scene->addChild(layer);
	return scene;
}
void LoadingEntryLayer::loadCallBack(CCObject* ped){
	loadingNum++;	 
    CCProgressTimer* pt=(CCProgressTimer*)this->getChildByTag(1);
	
	if(loadingNum<totalNum){
		float now=pt->getPercentage();
		pt->setPercentage(100.0/totalNum+now);
	}else{
		// �������ʱ����ת����Ӧ�Ľ���
		CCLOG("entry loading over");
		goEntryLayer();
	}
}


void LoadingEntryLayer::goEntryLayer(){
	CCScene* se= EntryLayer::scene();
	CCLOG("start change scene to entry layer");
	CCDirector::sharedDirector()->replaceScene(se);
}

bool LoadingEntryLayer::setUpdateView(){
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