#include "MaskSprites.h"
#include "ui/CocosGUI.h"

USING_NS_CC;


bool MaskSprites::init()
{
	return true;
}

//MaskSprites::MaskSprites()
//{
//}
//
//
//MaskSprites::~MaskSprites()
//{
//}

void MaskSprites::MaskOfBulletSprite()
{
	//CCLOG("MaskSprites::MaskOfBulletSprite()");
	
	//Sprite* maskOfBulletSprite = Sprite::create("mask1.png");
	//maskOfBulletSprite->setPosition(1100, 400);
	//this->addChild(maskOfBulletSprite);

	//auto actionMoveTo = MoveTo::create(5.0f, Vec2(-100, 400));
	//maskOfBulletSprite->runAction(actionMoveTo);
}

void MaskSprites::MaskOfSpeedUpSprite()
{
}

void MaskSprites::MaskOfFlySprite()
{
}

MaskSprites * MaskSprites::create()
{
	MaskSprites* ret = new (std::nothrow) MaskSprites();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		delete ret;
		ret = nullptr;
		return nullptr;
	}
}
