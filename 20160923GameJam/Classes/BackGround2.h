#ifndef __BACKGROUND2_H__
#define __BACKGROUND2_H__

#include "cocos2d.h"

class BackGround2 : public cocos2d::Layer
{
private:

	cocos2d::Sprite* m_bgLeft;
	cocos2d::Sprite* m_bgRight;

public:

	//static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt)override;

	CREATE_FUNC(BackGround2);
};

#endif // __HELLOWORLD_SCENE_H__
