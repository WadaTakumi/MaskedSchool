#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "MaskPower.h"
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "QueryCallback.h"

using namespace cocos2d;

class MainScene;

class Player : public cocos2d::Node
{
private:

	b2World* m_pWorld;
	b2Draw* m_pDraw;
	b2Body* m_pbPlayer;
	b2Vec2 m_p;

	cocos2d::Sprite* m_pPlayer;
	//cocos2d::Sprite* m_pIconOfNotGetMaskPower;
	//MaskPower* m_pBullet;
	//MainScene* m_main;
	
	//cocos2d::CCParticleSystemQuad* m_pParticletouch;
	//cocos2d::CCParticleSystemQuad* m_pParticleEat;

	int m_touchCount;
	float m_time;
	int m_timeCount;
	int m_randNum;
	//bool m_jumpFlag;
	//bool m_getMaskflag;
	//bool m_putOutMaskPowerButtonFlag;

public:

	//static cocos2d::Scene* createScene();
	Player::Player();
	Player::~Player();
	virtual bool init(b2World* world);
	//void update(float dt)override;

	bool onTouchBegan(
		cocos2d::Touch* touch,
		cocos2d::Event *unused_event);
	
	void jump(cocos2d::Ref * pSende);
	void putOutToMaskPowerButton();
	void useMaskPower(cocos2d::Ref * pSende);

	void jump();

	static Player* create(b2World* world);
};

#endif // __HELLOWORLD_SCENE_H__
