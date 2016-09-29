#ifndef __MAASK_OF_SCREEN_TO_SPEED_UP_H__
#define __MAASK_OF_SCREEN_TO_SPEED_UP_H__

//--インクルード----------------------------------------------------//
#include "cocos2d.h"
#include "BaseMask.h"
#include "BackGroundLayer.h"

//**************************************************************************************
//  MaskOfScreenToSpeedUpクラス
//**************************************************************************************
/*
【機能】
背景スクロールの速度上昇マスクのクラス
*/

class MaskOfScreenToSpeedUp : public BaseMask
{
private:

	BackgroundLayer* m_pBackgroundLayer;

public:
	//初期化
	virtual bool init();

	//マスクの能力を使う
	virtual void MaskAction();

};

#endif 