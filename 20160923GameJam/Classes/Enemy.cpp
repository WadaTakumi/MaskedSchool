#include "Enemy.h"
#include "ui/CocosGUI.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

const int PTM_RATIO = 32;

bool Enemy::init(b2World* world, EnemyData* data)
{
	m_world = world;

	m_type = RandomHelper::random_int(0, 2);

	m_enemy = data->getRandomEnemy(m_type);
	auto actionMoveByenemy = MoveBy::create(5.0, Vec2(-1500, 0));
	m_enemy->runAction(actionMoveByenemy);
	this->addChild(m_enemy);

	//m_bgRight = Sprite::create("bg2Right.png");
	//m_bgRight->setPosition(Vec2((visibleSize.width / 2 + (visibleSize.width / 2 / 2 / 1.46)),
	//	(visibleSize.height / 2)));
	//this->addChild(m_bgRight);

	//auto actionMoveBym_bgRight = MoveBy::create(70.0, Vec2(-1500, 0));
	//m_bgRight->runAction(actionMoveBym_bgRight);

	// Set enemy physics
	b2BodyDef enemyBodyDef;
	b2FixtureDef enemyFixtureDef;
	b2PolygonShape enemyDynamicBox;
	enemyDynamicBox.SetAsBox(1.0f, 1.0f);

	enemyBodyDef.type = b2_dynamicBody;
	enemyBodyDef.position.Set(m_enemy->getPosition().x, 
							  m_enemy->getPosition().y);
	enemyBodyDef.userData = m_enemy;
	m_enemyBody = m_world->CreateBody(&enemyBodyDef);

	enemyFixtureDef.shape = &enemyDynamicBox;
	m_enemyBody->CreateFixture(&enemyFixtureDef);

	m_hitOnHead = false;
	m_scheduledForRemoval = false;

	scheduleUpdate();


	return true;
}

void Enemy::update(float dt)
{
	// TODO add enemy colliders
	if (m_type == EnemyData::EnemyType::FLYING 
		&& m_hitOnHead)
	{
		// Stop default flying animation
		// and start falling animation
		m_enemy->stopActionByTag(1);
		m_enemy->runAction(this->getActionByTag(2));
	}

	//If(m_enemy.loc == ruudun ulkopuolella)
	//{
	//	  m_scheduledForRemoval = true;
	//}
}

Enemy* Enemy::create(b2World* world, EnemyData* data)
{
	Enemy* enemy = new(std::nothrow) Enemy();
	if (enemy && enemy->init(world, data))
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