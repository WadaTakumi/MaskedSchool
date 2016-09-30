#ifndef __BaseMask_H__  
#define __BaseMask_H__  

//--インクルード----------------------------------------------------//
#include "cocos2d.h"  


//**************************************************************************************
//  BaseMaskクラス
//**************************************************************************************
/*
【機能】
マスクの基本クラス
*/

class BaseMask : public cocos2d::Node
{
private:
public:

	cocos2d::Vec2 Player_pos;

	//マスクの画像
	cocos2d::Sprite* m_mask;

	//初期化
	virtual bool init();

	//マスクの能力を使う
	virtual void MaskAction() {};

	void GetPos(cocos2d::Vec2 pos);


	CREATE_FUNC(BaseMask)

};
#endif   