#ifndef __BaseMask_H__  
#define __BaseMask_H__  

//--�C���N���[�h----------------------------------------------------//
#include "cocos2d.h"  


//**************************************************************************************
//  BaseMask�N���X
//**************************************************************************************
/*
�y�@�\�z
�}�X�N�̊�{�N���X
*/

class BaseMask : public cocos2d::Node
{
private:


public:

	//�}�X�N�̉摜
	cocos2d::Sprite* m_mask;

	//������
	virtual bool init();

	//�}�X�N�̔\�͂��g��
	virtual void MaskAction();

};
#endif   