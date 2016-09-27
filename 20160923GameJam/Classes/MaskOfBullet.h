#ifndef __MAASK_OF_BULLET_H__
#define __MAASK_OF_BULLET_H__

//--インクルード----------------------------------------------------//
#include "cocos2d.h"
#include "BaseMask.h"

//**************************************************************************************
//  MaskOfBulletクラス
//**************************************************************************************
/*
【機能】
玉を打つマスクのクラス
*/

class MaskOfBullet : public BaseMask
{
public:
	//初期化
	virtual bool init();

	//マスクの能力を使う
	virtual void MaskAction();

};

#endif 