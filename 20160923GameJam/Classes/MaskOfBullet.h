#ifndef __MAASK_OF_BULLET_H__
#define __MAASK_OF_BULLET_H__

//--�C���N���[�h----------------------------------------------------//
#include "cocos2d.h"
#include "BaseMask.h"
#include "Player.h"

//**************************************************************************************
//  MaskOfBullet�N���X
//**************************************************************************************
/* \
�y�@�\�z
�ʂ�ł}�X�N�̃N���X
*/

class MaskOfBullet : public BaseMask
{
private:

public:

	//cocos2d::Sprite* m_mask;

	//������
	virtual bool init();

	//�}�X�N�̔\�͂��g��
	virtual void MaskAction();

	CREATE_FUNC(MaskOfBullet)

};

#endif 