#ifndef __MASKPOWER_H__
#define __MASKPOWER_H__


#include "cocos2d.h"

class MaskPower : public cocos2d::Layer
{
private:
	cocos2d::Sprite* m_Bullet;
//	Player* m_pPlayer;
	//cocos2d::Sprite* m_bgRight;

public:

	//static cocos2d::Scene* createScene();

	virtual bool init();
//	void update(float dt)override;

	CREATE_FUNC(MaskPower);
};

#endif // __HELLOWORLD_SCENE_H__
