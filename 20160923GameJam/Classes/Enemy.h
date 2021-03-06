#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "cocos2d\cocos\2d\CCSpriteFrame.h"
#include "Box2D\Box2D.h"
#include "EnemyData.h"

class Enemy : public cocos2d::Layer
{
public:
	cocos2d::Sprite* m_enemy;
	EnemyData::EnemyType m_type;
	Animate* m_flyingAnimation;
	Animate* m_hitAnimation;
	Vector<SpriteFrame*> m_birdFlyingFrames;
	Vector<SpriteFrame*> m_birdHitFrames;
	//cocos2d::Sprite* m_bgRight;

	// Physics
	b2World* m_world;
	b2Body* m_enemyBody;

	bool m_hitOnHead; // TODO rename?
	bool m_scheduledForRemoval;
	bool StartSpawnEnemyFlag = true;

	//static cocos2d::Scene* createScene();

	virtual bool init(b2World* world);
	void update(float dt)override;

	void StartSpawnEnemy(float delta);
	void SpawnEnemy(float delta);

	static Enemy* create(b2World* world);
};

#endif // __HELLOWORLD_SCENE_H__
