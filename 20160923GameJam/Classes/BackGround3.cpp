#include "BackGround3.h"
#include "ui/CocosGUI.h"
#include <string>

USING_NS_CC;

using namespace std;

bool BackGround3::init()
{
	Bg = Sprite::create("huji.png");
	Bg->setPosition(Vec2((960 / 2), (640 / 2)));
	Bg->setScale(20);
	this->addChild(Bg);


	scheduleUpdate();


	return true;
}

//void BackGround::update(float dt)
//{
//}