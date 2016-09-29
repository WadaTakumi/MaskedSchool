#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "BackGround.h"
#include "BackGround2.h"
#include "BackGround3.h"
#include "BackGroundLayer.h"
#include "BaseMask.h"
#include "MaskOfBullet.h"
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "QueryCallback.h"

class Player;
class Enemy;


class MainScene : public cocos2d::Layer
{
private:

	b2World* m_pWorld;
	b2Draw* m_pDraw;
	b2Vec2 m_position;
	b2Body* m_groundBody;
	b2Body* m_bodyA;	// BOX2D‚Ì“–‚½‚è”»’è—p
	b2Body* m_bodyB;	// BOX2D‚Ì“–‚½‚è”»’è—p
	BackGround* m_pBackGround;
	BackgroundLayer* m_pBackGroundLayer;
	BackGround2* m_pBackGround2;
	BackGround3* m_pBackGround3;
	Player* m_pPlayer;
	Enemy* m_pEnemy;
	BaseMask* m_pbaseMask;


	int pPrintTimeCount;
	float m_time;
	int m_timeCount;
	bool m_getMaskflag;
	bool m_notJampFlag;

public:

	static cocos2d::Scene* createScene();

	MainScene();
	~MainScene();

	virtual bool init();
	void update(float dt)override;
	void initPhysics();
	void draw(cocos2d::Renderer* renderer,
		const cocos2d::Mat4 &transform,
		uint32_t flags);
	bool onTouchBegan(cocos2d::Touch * touch,
		cocos2d::Event * unused_event);

	void BeginContact(b2Contact* contact);

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
};

#endif // __HELLOWORLD_SCENE_H__
