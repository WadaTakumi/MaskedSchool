#ifndef __CutinOfStart__
#define __CutinOfStart__

#include "cocos2d.h"

class CutInOfStart:public cocos2d::Node
{
private:

	float m_time;
	int m_timeCount;
	bool m_timeflag;

public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt)override;
//	void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags);
	void cutInAction();
	void setCutInFlag(bool flag);
	bool getCutinFlag();
	static CutInOfStart* create();
};

#endif