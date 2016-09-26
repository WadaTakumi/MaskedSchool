#include "Enemy.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool Enemy::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();


	m_enemy = Sprite::create("enemy.png");
	m_enemy->setPosition(Vec2((960 / 2) + 850, (640 / 2) + 50));
	this->addChild(m_enemy);

	//m_bgRight = Sprite::create("bg2Right.png");
	//m_bgRight->setPosition(Vec2((visibleSize.width / 2 + (visibleSize.width / 2 / 2 / 1.46)),
	//	(visibleSize.height / 2)));
	//this->addChild(m_bgRight);


	// アクション（スクロール）
	auto actionMoveByenemy = MoveBy::create(10.0, Vec2(-1500, 0));
	m_enemy->runAction(actionMoveByenemy);
	//auto actionMoveBym_bgRight = MoveBy::create(70.0, Vec2(-1500, 0));
	//m_bgRight->runAction(actionMoveBym_bgRight);



	scheduleUpdate();


	return true;
}

void Enemy::update(float dt)
{

}