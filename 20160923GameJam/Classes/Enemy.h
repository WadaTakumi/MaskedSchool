#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "cocos2d\cocos\2d\CCSpriteFrame.h"
#include "Box2D\Box2D.h"

enum EnemyType
{
	CAR = 0,		// Fast mover
	BIRD = 1,		// Flying
	JUMPING = 2,		// Jumping (TBD)
};
class Enemy : public cocos2d::Layer
{
private:
	cocos2d::Sprite* m_enemy;
	EnemyType m_type;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_birdFlyingFrames;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_birdHitFrames;
	//cocos2d::Sprite* m_bgRight;

	// Physics
	b2World* m_world;
	b2Body* m_enemyBody;

public:

	//static cocos2d::Scene* createScene();

	virtual bool init(b2World* world);
	void update(float dt)override;

	static Enemy* create(b2World* world);
};

#endif // __HELLOWORLD_SCENE_H__
