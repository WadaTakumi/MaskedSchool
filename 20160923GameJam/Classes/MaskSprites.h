#ifndef __MAASK_SPRITES_H__
#define __MAASK_SPRITES_H__

//--インクルード----------------------------------------------------//
#include "cocos2d.h"
//#include "BaseMask.h"
//#include "Player.h"

//**************************************************************************************
//  マスクの画像クラス
//**************************************************************************************
/* \
【機能】
マスクの画像が積み込んである
*/

class MaskSprites : public cocos2d::Node
{
private:
	//cocos2d::Sprite* maskOfBulletSprite;
public:

	//cocos2d::Sprite* m_mask;

	//初期化
	virtual bool init();

	//弾を打つマスクの画像
	void MaskOfBulletSprite();

	//スピードアップマスクの画像
	void MaskOfSpeedUpSprite();

	void MaskOfFlySprite();

	static MaskSprites* create();

};

#endif 