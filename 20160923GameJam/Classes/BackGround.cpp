#include "BackGround.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool BackGround::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Bg = Sprite::create("block.png");
	Bg->setPosition(Vec2((960 / 2/2), (640 / 2) + 10));
//	Bg->setScale(20);
	this->addChild(Bg);

	Bg2 = Sprite::create("block.png");
	Bg2->setPosition(Vec2((960 / 2), (640 / 2) + 10));
	//	Bg->setScale(20);
	this->addChild(Bg2);

	Bg3 = Sprite::create("block.png");
	Bg3->setPosition(Vec2((960 / 2)+400, (640 / 2) + 10));
	//	Bg->setScale(20);
	this->addChild(Bg3);

	Bg4 = Sprite::create("block.png");
	Bg4->setPosition(Vec2((960 / 2)+800 , (640 / 2) + 10));
	//	Bg->setScale(20);
	this->addChild(Bg4);

	auto Bg5 = Sprite::create("block.png");
	Bg5->setPosition(Vec2((960 / 2) + 1200, (640 / 2) + 10));
	//	Bg->setScale(20);
	this->addChild(Bg5);


	auto actionMoveBy = MoveBy::create(10.0, Vec2(-1500, 0));
	Bg->runAction(actionMoveBy);

	auto actionMoveBy2 = MoveBy::create(10.0, Vec2(-1500, 0));
	Bg2->runAction(actionMoveBy2);
	
	auto actionMoveBy3 = MoveBy::create(10.0, Vec2(-1500, 0));
	Bg3->runAction(actionMoveBy3);
	
	auto actionMoveBy4 = MoveBy::create(10.0, Vec2(-1500, 0));
	Bg4->runAction(actionMoveBy4);

	

	//scheduleUpdate();


	return true;
}

//void BackGround::update(float dt)
//{
//}