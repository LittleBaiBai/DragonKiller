#include "BirdSystem.h"
USING_NS_CC;
BirdSystem::BirdSystem(){
	maxBirdNumber = 20;
	birdArray = CCArray::createWithCapacity(maxBirdNumber);
	birdArray->retain();
}

void BirdSystem::setGameLayer(GameLayer* layer){
	this->gameLayer = layer;
}

void BirdSystem::addOneBird(float){
	if(!tooManyBirds()){
        CCLOG("Add one bird!!");
        BirdClippingNode* bird = new BirdClippingNode();
        birdArray->addObject(bird);
        this->gameLayer->addChild(bird);
        this->gameLayer->addChild(bird->bird,10);
        bird->birdStartActions();
    }
	return;
}

bool BirdSystem::tooManyBirds(){
    CCLOG("now bird count = %d, maxBirdNum = %d", birdArray->count(), maxBirdNumber);
    if(birdArray->count() > maxBirdNumber - 3 && birdArray->count() < maxBirdNumber){
        CCLOG("start warning!!");
        this->gameLayer->gameBackground->showOverWarning();
    }
    else if(birdArray->count() >= maxBirdNumber){
        CCLOG("Game Over!!!");
        this->gameLayer->dragonWin();
    }
    else if(birdArray->count() <= maxBirdNumber - 3)
        this->gameLayer->gameBackground->removeOverWarning();
    if(birdArray->count() < maxBirdNumber){
        return false;
    }
    return true;
}

void BirdSystem::showBirds(){
	CCLOG("Show birds!");
	schedule(schedule_selector(BirdSystem::addOneBird),5);
	schedule(schedule_selector(BirdSystem::resumeOneHole),10);
}

void BirdSystem::resumeOneHole(float){
	CCPoint resumeTarget;
	if(this->gameLayer->monsterSystem->dragonHoleArray->count() > 0){
		resumeTarget = ((CCSprite*)(this->gameLayer->monsterSystem->dragonHoleArray->objectAtIndex(0)))->getPosition();
        CCLOG("----------HOLES------------------");
        for(int i = 0; i < this->gameLayer->monsterSystem->dragonHoleArray->count(); i++){
            CCLOG("%d,%f, %f",i,((CCSprite*)(this->gameLayer->monsterSystem->dragonHoleArray->objectAtIndex(i)))->getPositionX(),((CCSprite*)(this->gameLayer->monsterSystem->dragonHoleArray->objectAtIndex(i)))->getPositionY());
        }
		CCLOG("resumeTarget x = %f, y = %f", resumeTarget.x, resumeTarget.y);
        CCLOG("----------BIRDS------------------");
		for(int i = 0; i < this->birdArray->count(); i++){
			CCLOG("%d,%f, %f",i,((BirdClippingNode*)(this->birdArray->objectAtIndex(i)))->bird->getPositionX(),((BirdClippingNode*)(this->birdArray->objectAtIndex(i)))->bird->getPositionY());
		}
        
		if(this->birdArray->count() > 0){
			resumeBird = (BirdClippingNode*)(this->birdArray->objectAtIndex(0));
            CCLOG("********before resume a hole bird at %f, %f", resumeBird->bird->getPositionX(), resumeBird->bird->getPositionY());
            CCLOG("********before resume a hole clipping bird at %f, %f", resumeBird->getPositionX(), resumeBird->getPositionY());
			float duration = resumeBird->resumeOneHole(resumeTarget);
          //  CCActionInterval* moveTo = CCMoveTo::create(4,resumeTarget);
           //// CCScaleTo* scaleTo=CCScaleTo::create(3.f, 0);
            //CCCallFunc* changePic = CCCallFunc::create(this,callfunc_selector(BirdClippingNode::wearCrown));
         //   CCSequence* ccs = CCSequence::create(moveTo, scaleTo, NULL);
         //   resumeBird->bird->runAction(moveTo);
		//	CCLOG("birdcount = %d, holescount = %d", birdArray->count(), this->gameLayer->monsterSystem->dragonHoleArray->count());
			scheduleOnce(schedule_selector(BirdSystem::afterResumeOneHole),duration);
		}
	}
}

void BirdSystem::afterResumeOneHole(float){
	CCLOG("after resume a hole bird locate at %f, %f",
		resumeBird->bird->getPositionX(),resumeBird->bird->getPositionY());
    CCLOG("after resume a hole clipping bird locate at %f, %f",
          resumeBird->getPositionX(),resumeBird->getPositionY());
	CCLOG("birdcount = %d, holescount = %d", birdArray->count(), this->gameLayer->monsterSystem->dragonHoleArray->count());
	this->gameLayer->removeChild(resumeBird->bird);
	this->gameLayer->removeChild(resumeBird);
	this->gameLayer->monsterSystem->dragonHolesStencil->removeChild((CCNode*)this->gameLayer->monsterSystem->dragonHoleArray->objectAtIndex(0));
	this->gameLayer->monsterSystem->dragonHoleArray->removeObjectAtIndex(0);
	this->birdArray->removeObjectAtIndex(0);
	this->gameLayer->monsterSystem->setBloodPercentage(this->gameLayer->monsterSystem->bloodBar->getPercentage() + 5);
}

int BirdSystem::attackBird(CCPoint target){
	do{
	int i;
	CC_BREAK_IF(!birdArray);
	CCLOG("BirdSystem: try attack bird, target x = %f, target y = %f, totoal birds = %d",target.x, target.y, birdArray->count()); 
	for( i = 0; i < birdArray->count(); i++){
		BirdClippingNode* bird = (BirdClippingNode*)birdArray->objectAtIndex(i);
		CCLOG("bird %d locate at x = %f, y = %f", i, bird->bird->getPositionX(), bird->bird->getPositionY());
		if(bird->isAttacked(target) == 1 && bird != resumeBird){
			CCLOG("&&&&&&&&&&&&attacking bird x = %f, y = %f",bird->bird->getPositionX(),bird->bird->getPositionY());
			//ÄñÏûÊ§
			removeBirdIndex = i;
			scheduleOnce(schedule_selector(BirdSystem::removeBird),1.f);
			return 1;
		}
	}
	}while(0);
	return 0;
}

void BirdSystem::removeBird(float){
    this->gameLayer->removeChild(((BirdClippingNode*)birdArray->objectAtIndex(removeBirdIndex))->bird);
	this->gameLayer->removeChild((BirdClippingNode*)birdArray->objectAtIndex(removeBirdIndex));
	birdArray->removeObjectAtIndex(removeBirdIndex);
}