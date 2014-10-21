#include "LoadingGameLayer.h"
USING_NS_CC;
LoadingGameLayer::LoadingGameLayer(){
	this->loadingNum=0;
	this->totalNum=49;
}
bool LoadingGameLayer::init(){
	CCLOG("%d                              '''''''",this->totalNum);
	bool isRet=false;
	do 
	{
        CC_BREAK_IF(!BaseLayer::init());
        CC_BREAK_IF(!this->setUpdateView());
        
        //10
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/warning_1.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack)); // Ҫ��ʱ�ĺ��
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/warning_2.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/warning_3.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/background.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack)); // ��Ϸ����
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/cloud_near_1.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack)); // ��Ϸ����
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/cloud_near_2.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack)); // ��������
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/cloud_middle_1.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack)); //  �����ӵ�
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/cloud_middle_2.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack)); // Ѫ������
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/cloud_far_1.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack)); //  Ѫ��
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/cloud_far_2.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack)); //  Ѫ��
        
        //CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/back_bubble.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));//���������
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/front_bubble.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));//ǰ�������
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/dragon_shadow.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));//������Ӱ
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/decoration.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));//���ϵ�װ��
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/dragon_win.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));//dragon win��
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/game_over_stamp.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));//����������
        //15
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg/dragon_win_8.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));//dragon win��
//        for (int i = 1; i <= 8; i++) {
//            CCTextureCache::sharedTextureCache()->addImageAsync(CCString::createWithFormat("gamebg/dragon_win_%d.png",i)->getCString(),this,callfuncO_selector(LoadingGameLayer::loadCallBack));
//        }
        
        CCTextureCache::sharedTextureCache()->addImageAsync("game/dragon.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));//��
        CCTextureCache::sharedTextureCache()->addImageAsync("game/dragon_bg.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));//�������
        //25
        CCTextureCache::sharedTextureCache()->addImageAsync("game/lama_heads.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("game/lama_legs.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pilot/lama_blink.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pilot/lama_face.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pilot/lama_whole.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pilot/lama_saliva.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pilot/lama_saliva_short.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pilot/lama_spit.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        //33
        CCTextureCache::sharedTextureCache()->addImageAsync("game/bird_1.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("game/bird_2.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("game/bird_3.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("game/bird_dead.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("game/bird_hole_filler.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("game/saliva_pool.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("game/dragon_eye_opened.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("game/dragon_eye_closed.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        //41
        CCTextureCache::sharedTextureCache()->addImageAsync("pause/bend_1.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pause/bend_2.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pause/bend_3.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pause/bend_4.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pause/bend_5.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pause/bend_eat_1.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pause/bend_eat_2.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pause/bend_eat_3.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pause/button_resume.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pause/button_restart.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("pause/button_menu.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        //52
        CCTextureCache::sharedTextureCache()->addImageAsync("scene/tap_to_continue_1.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("scene/clock_1.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("scene/clock_2.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("scene/clock_3.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("scene/clock_0.png",this,callfuncO_selector(LoadingGameLayer::loadCallBack));
        //57
        isRet=true;
	} while (0);
	return isRet;
}
CCScene* LoadingGameLayer::scene(){
	CCScene* scene=CCScene::create();
	LoadingGameLayer* layer=LoadingGameLayer::create();
	scene->addChild(layer);
	return scene;
}
void LoadingGameLayer::loadCallBack(CCObject* ped){
	loadingNum++;	 
    CCProgressTimer* pt=(CCProgressTimer*)this->getChildByTag(1);
	
	if(loadingNum<totalNum){
		float now=pt->getPercentage();
		pt->setPercentage(100.0/totalNum+now);
		CCLOG("set pt percentage = %f", 100.0/totalNum+now);
	}else{
		// �������ʱ����ת����Ӧ�Ľ���
		CCLOG("loading over");
		goGameLayer();
	}
}


void LoadingGameLayer::goGameLayer(){
	//CCScene* se=EntryLayer::scene();
	CCScene* se=GameLayer::scene();
	CCLOG("start change scene to game layer");
	CCDirector::sharedDirector()->replaceScene(se);
}

bool LoadingGameLayer::setUpdateView(){
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
        
        // ���ӽ�����
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