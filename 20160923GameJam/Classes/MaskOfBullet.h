#ifndef __MAASK_OF_BULLET_H__
#define __MAASK_OF_BULLET_H__

//--�C���N���[�h----------------------------------------------------//
#include "cocos2d.h"
#include "BaseMask.h"
#include "Player.h"

//**************************************************************************************
//  MaskOfBullet�N���X
//**************************************************************************************
/*
�y�@�\�z
�ʂ�ł}�X�N�̃N���X
*/

class MaskOfBullet : public BaseMask
{
private:

	Player* m_pPlayer;

public:
	//������
	virtual bool init();

	//�}�X�N�̔\�͂��g��
	virtual void MaskAction();

};

#endif 