#include "Enemy.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool Enemy::init()
{
	int eType = RandomHelper::random_int(0, 2);
	//if (eType == CAR)
	//{
	//	// Init CAR type enemy
	//	m_type == CAR;
	//	m_enemy = Sprite::create("PixelCar.png");
	//	m_enemy->setScale(1.5);
	//	m_enemy->setPosition(Vec2((960 / 2) + 850, (640 / 2) + 50));

	//// アクション（スクロール）
	//auto actionMoveByenemy = MoveBy::create(3.0, Vec2(-1500, 0));
	//m_enemy->runAction(actionMoveByenemy);
	//}
	//else if (eType == BIRD)
	//{
		// init BIRD type enemy
		m_type = BIRD;
		char str[100];
		// Load chicken animation
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("chicken/flying/flying.plist");
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		Vec2 visibleSize = Director::getInstance()->getVisibleSize();
		for (int i = 0; i < 3; ++i)
		{
			auto spriteCache = SpriteFrameCache::getInstance();
			sprintf(str, "flying%d.png", i);
			m_flyingFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}
		auto animation = Animation::createWithSpriteFrames(m_flyingFrames, 0.1f);
		auto animate = Animate::create(animation);
		// TODO FIX ANIMATION
		m_enemy = Sprite::createWithSpriteFrame(m_flyingFrames.front());
		m_enemy->setScale(0.3);
		m_enemy->setPosition(Vec2((960 / 2) + 850, (640 / 2) + 70));
		m_enemy->runAction(RepeatForever::create(animate));

		auto actionMoveByenemy = MoveBy::create(5.0, Vec2(-1500, 0));
		m_enemy->runAction(actionMoveByenemy);
	//}

	//else if (eType == TEMP)
	//{
	//	// Init TEMP type enemy
	//	m_type == TEMP;
	//	m_enemy = Sprite::create("enemy.png");
	//	m_enemy->setPosition(Vec2((960 / 2) + 850, (640 / 2) + 50));
	//}

	this->addChild(m_enemy);

	//m_bgRight = Sprite::create("bg2Right.png");
	//m_bgRight->setPosition(Vec2((visibleSize.width / 2 + (visibleSize.width / 2 / 2 / 1.46)),
	//	(visibleSize.height / 2)));
	//this->addChild(m_bgRight);

	//auto actionMoveBym_bgRight = MoveBy::create(70.0, Vec2(-1500, 0));
	//m_bgRight->runAction(actionMoveBym_bgRight);



	scheduleUpdate();


	return true;
}

void Enemy::update(float dt)
{

}