#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "BackGround.h"
#include "BackGround2.h"
#include "BackGround3.h"
#include "MaskOfBullet.h"
#include "cocos2d.h"

class Player;
class Enemy;

class MainScene : public cocos2d::Layer
{
private:

	BackGround* m_pBackGround;
	BackGround2* m_pBackGround2;
	BackGround3* m_pBackGround3;
	Player* m_pPlayer;
	Enemy* m_pEnemy;
	MaskOfBullet* m_pMaskOfBullet;

	int pPrintTimeCount;
	float m_time;
	int m_timeCount;
	bool m_getMaskflag;

public:

	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt)override;

	void collisionDetection();
	bool getGetMaskflag();

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
};

#endif // __HELLOWORLD_SCENE_H__
