#include "MaskPower.h"
#include "Player.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool MaskPower::init()
{
	//Player* m_pPlayer = Player::create();
	//this->addChild(m_pPlayer);

	m_Bullet = Sprite::create("Bullet.png");
	//m_Bullet->setPosition(Vec2(m_pPlayer->getPosition()));
	//m_Bullet->setPosition(Vec2(m_pPlayer->getPosition()));
	//m_Bullet->setScale(20);
	this->addChild(m_Bullet);

	auto actionMoveBy = MoveBy::create(5.0, Vec2(1500, 0));
	m_Bullet->runAction(actionMoveBy);


	//scheduleUpdate();

	return true;
}

//void MaskPower::update(float dt)
//{
//}