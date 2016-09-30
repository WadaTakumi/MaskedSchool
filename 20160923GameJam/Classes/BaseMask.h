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

	Player*m_Player;

	//マスクの画像
	cocos2d::Sprite* m_mask;

	//初期化
	virtual bool init();

	//マスクの能力を使う
	virtual void MaskAction() {};


	CREATE_FUNC(BaseMask)

	void GetPlayer(Player*player);

};
#endif   