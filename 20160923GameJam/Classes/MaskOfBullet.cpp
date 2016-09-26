#include "MaskOfBullet.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool MaskOfBullet::init()
{
	//Size visibleSize = Director::getInstance()->getVisibleSize();


	m_mask = Sprite::create("mask1.png");
	m_mask->setPosition(Vec2((960 / 2) + 350, (640 / 2) + 200));
	this->addChild(m_mask);


	// アクション（スクロール）
	auto actionMoveBym_bgLeft = MoveBy::create(10.0, Vec2(-1500, 0));
	m_mask->runAction(actionMoveBym_bgLeft);


	//scheduleUpdate();


	return true;
}

//void MaskOfBullet::update(float dt)
//{
//
//}