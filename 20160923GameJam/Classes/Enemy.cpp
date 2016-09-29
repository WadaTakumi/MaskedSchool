#include "Enemy.h"
#include "ui/CocosGUI.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

bool Enemy::init(b2World* world)
{
	m_world = world;

	int eType = RandomHelper::random_int(0, 2);
	if (eType == CAR)
	{
		// Init CAR type enemy
		m_type = CAR;
		m_enemy = Sprite::create("PixelCar.png");
		m_enemy->setScale(1.2f);
		m_enemy->setPosition(Vec2((960 / 2) + 850, (640 / 2) + 50));

	// アクション（スクロール）
	auto actionMoveByenemy = MoveBy::create(3.0, Vec2(-1500, 0));
	m_enemy->runAction(actionMoveByenemy);
	}
	else if (eType == BIRD)
	{
		// init BIRD type enemy
		m_type = BIRD;
		char str[100];
		// Load chicken animation
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("chicken/flying/flying.plist");
		for (int i = 0; i < 3; ++i)
		{
			auto spriteCache = SpriteFrameCache::getInstance();
			sprintf(str, "frame-%d.png", i);
			m_birdFlyingFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}
		// Default BIRD type enemy animation
		auto animation = Animation::createWithSpriteFrames(m_birdFlyingFrames, 0.07f);
		auto flyAnimate = Animate::create(animation);

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("chicken/flying/hit.plist");
		for (int i = 0; i < 1; ++i)
		{
			auto spriteCache = SpriteFrameCache::getInstance();
			sprintf(str, "frame-%d.png", i);
			m_birdHitFrames.pushBack(spriteCache->getSpriteFrameByName(str));
		}
		// Activate this when a BIRD type enemy gets hit
		animation = Animation::createWithSpriteFrames(m_birdHitFrames, 0.07f);

		m_enemy = Sprite::createWithSpriteFrame(m_birdFlyingFrames.front());
		m_enemy->setScale(0.15f);
		m_enemy->setPosition(Vec2((960 / 2) + 850, (640 / 2) + 70));
		m_enemy->runAction(RepeatForever::create(flyAnimate));

		auto actionMoveByenemy = MoveBy::create(5.0, Vec2(-1500, 0));
		m_enemy->runAction(actionMoveByenemy);
	}

	else if (eType == JUMPING)
	{
		// Init JUMPING type enemy
		m_type = JUMPING;
		m_enemy = Sprite::create("food.png");
		m_enemy->setPosition(Vec2((960 / 2) + 850, (640 / 2) + 50));
		m_enemy->setScale(0.15f);
		auto actionMoveByenemy = MoveBy::create(3.0, Vec2(-1500, 0));
		m_enemy->runAction(actionMoveByenemy);
	}

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

Enemy* Enemy::create(b2World* world)
{
	Enemy* enemy = new(std::nothrow) Enemy();
	if (enemy && enemy->init(world))
	{
		enemy->autorelease();
		return enemy;
	}
	else
	{
		delete enemy;
		enemy = nullptr;
		return nullptr;
	}
}