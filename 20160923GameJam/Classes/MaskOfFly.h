#ifndef __MAASK_OF_FLY_H__
#define __MAASK_OF_FLY_H__

//--�C���N���[�h----------------------------------------------------//
#include "cocos2d.h"
#include "BaseMask.h"
#include "Player.h"

//**************************************************************************************
//  MaskOfFly�N���X
//**************************************************************************************
/*
�y�@�\�z
2�i�W�����v�}�X�N�̃N���X
*/

class MaskOfFly : public BaseMask
{
private:

	Back* m_pPlayer;

public:
	//������
	virtual bool init();

	//�}�X�N�̔\�͂��g��
	virtual void MaskAction();

};

#endif 