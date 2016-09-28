#ifndef __MASKPOWER_H__
#define __MASKPOWER_H__


#include "cocos2d.h"

class MaskPower : public cocos2d::Layer
{
private:
	cocos2d::Sprite* m_Bullet;

public:

	virtual bool init();

	CREATE_FUNC(MaskPower);
};

#endif // __HELLOWORLD_SCENE_H__
