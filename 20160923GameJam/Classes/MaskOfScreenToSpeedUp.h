#ifndef __MAASK_OF_SCREEN_TO_SPEED_UP_H__
#define __MAASK_OF_SCREEN_TO_SPEED_UP_H__

//--�C���N���[�h----------------------------------------------------//
#include "cocos2d.h"
#include "BaseMask.h"
#include "BackGroundLayer.h"

//**************************************************************************************
//  MaskOfScreenToSpeedUp�N���X
//**************************************************************************************
/*
�y�@�\�z
�w�i�X�N���[���̑��x�㏸�}�X�N�̃N���X
*/

class MaskOfScreenToSpeedUp : public BaseMask
{
private:

	BackgroundLayer* m_pBackgroundLayer;

public:
	//������
	virtual bool init();

	//�}�X�N�̔\�͂��g��
	virtual void MaskAction();

};

#endif 