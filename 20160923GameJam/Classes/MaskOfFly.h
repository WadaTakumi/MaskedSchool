#ifndef __MAASK_OF_FLY_H__
#define __MAASK_OF_FLY_H__

//--インクルード----------------------------------------------------//
#include "cocos2d.h"
#include "BaseMask.h"

//**************************************************************************************
//  MaskOfFlyクラス
//**************************************************************************************
/*
【機能】
2段ジャンプマスクのクラス
*/

class MaskOfFly : public BaseMask
{
public:
	//初期化
	virtual bool init();

	//マスクの能力を使う
	virtual void MaskAction();

};

#endif 