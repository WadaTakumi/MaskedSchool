#include "Enemy.h"
#include "ui/CocosGUI.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

const int PTM_RATIO = 32;

bool Enemy::init(b2World* world, EnemyData* data)
{
	m_world = world;

	m_type = static_cast<EnemyData::EnemyType>(RandomHelper::random_int(0, 2));

	m_enemy = data->getEnemyByType(m_type);

	if (!m_enemy)
		return false;

	// Set enemy physics
	b2BodyDef enemyBodyDef;
	b2FixtureDef enemyFixtureDef;
	b2PolygonShape enemyDynamicBox;
	enemyDynamicBox.SetAsBox(1.0f, 1.0f);

	enemyBodyDef.gravityScale = 3.0f;
	enemyFixtureDef.friction = 0.0f;
	enemyBodyDef.type = b2_dynamicBody;
	enemyBodyDef.position.Set(m_enemy->getPosition().x,
							  m_enemy->getPosition().y);
	m_enemyBody = m_world->CreateBody(&enemyBodyDef);
	//m_enemyBody->SetUserData(this); // TODO: fix invisible sprite

	enemyFixtureDef.shape = &enemyDynamicBox;
	m_enemyBody->CreateFixture(&enemyFixtureDef);

	m_hitOnHead = false;
	m_scheduledForRemoval = false;

	// Set default enemy actions
	if (m_type == EnemyData::GROUND)
	{
		// Init movement
		auto actionMoveByenemy = MoveBy::create(3.0, Vec2(-1500, 0));
		m_enemy->runAction(actionMoveByenemy);
	}
	else if (m_type == EnemyData::FLYING)
	{
		// Init animation and movement
		m_enemy->runAction(RepeatForever::create(data->getFlyingAnimation()));
		auto actionMoveByEnemy = MoveBy::create(5.0, Vec2(-1500, 0));
		m_enemy->runAction(actionMoveByEnemy);
	}

	this->addChild(m_enemy);

	scheduleUpdate();


	return true;
}

void Enemy::update(float dt)
{
	// TODO add enemy colliders
	if (m_type == EnemyData::FLYING && m_hitOnHead)
	{
		// Stop default flying animation
		// and start falling animation
		m_enemy->stopActionByTag(1);
		m_enemy->runAction(this->getActionByTag(2));
	}
	else if (dt >= 3.0f && m_type == EnemyData::JUMPING)
	{
		// Init jumping and movement
		b2Vec2 impulse(0, 8.0f);
		b2Vec2 point = m_enemyBody->GetWorldCenter();
		m_enemyBody->ApplyLinearImpulse(impulse, point, true);
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