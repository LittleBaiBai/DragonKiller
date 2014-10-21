#include "FlyLamaSystem.h"

USING_NS_CC;
FlyLamaSystem::FlyLamaSystem(){
	this->flyingLamas = CCArray::create();
	CCLOG("FlyLamaSystem init");
}

FlyLamaSystem::~FlyLamaSystem(){}

void FlyLamaSystem::setGameLayer(GameLayer* GameLayer){
	this->gameLayer=GameLayer;
}


void FlyLamaSystem::produceLamas(int count){
	CCLOG("produceLamas");
	for(int i = 0; i < count; i++){
		CCLOG("produce Lama %d",i);
		this->flyingLamas->addObject(new FlyLamaSprite(gameLayer));
	}
	flyingLamas->retain();
}

void FlyLamaSystem::showLamas(int count){
	count = count < this->flyingLamas->count() ? count : this->flyingLamas->count();

	for(int i = 0; i < count; i++){
		FlyLamaSprite* gls = (FlyLamaSprite*)this->flyingLamas->objectAtIndex(i);
		if(this->gameLayer){
			this->gameLayer->addChild(gls, 1);
			this->gameLayer->addChild(gls->lamaBody,3);
			this->gameLayer->addChild(gls->lamaSaliva,3);
			this->gameLayer->addChild(gls->lamaFace,3);
			gls->startMove();
		}
	}
}

void FlyLamaSystem::TouchToSpit(CCPoint target) {
	int count = this->flyingLamas->count();
	float minDist = 100000;
	int minIndex = -1;
	for(int i = 0; i < count; i++){
		FlyLamaSprite* gls = (FlyLamaSprite*)this->flyingLamas->objectAtIndex(i);
		if (gls->readyToAttack) {
			float dist = gls->getHorizontalDist(target.x);
			if (dist < minDist) {
				minIndex = i;
				minDist = dist;
			}
		}
	}
	if (minIndex != -1) {
		FlyLamaSprite* gls = (FlyLamaSprite*)this->flyingLamas->objectAtIndex(minIndex);
		gls->Spit(target);
	}
}