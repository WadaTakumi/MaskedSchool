#ifndef __MAASK_SPRITES_H__
#define __MAASK_SPRITES_H__

//--�C���N���[�h----------------------------------------------------//
#include "cocos2d.h"
//#include "BaseMask.h"
//#include "Player.h"

//**************************************************************************************
//  �}�X�N�̉摜�N���X
//**************************************************************************************
/* \
�y�@�\�z
�}�X�N�̉摜���ςݍ���ł���
*/

class MaskSprites : public cocos2d::Node
{
private:
	//cocos2d::Sprite* maskOfBulletSprite;
public:

	//cocos2d::Sprite* m_mask;

	//������
	virtual bool init();

	//�e��ł}�X�N�̉摜
	void MaskOfBulletSprite();

	//�X�s�[�h�A�b�v�}�X�N�̉摜
	void MaskOfSpeedUpSprite();

	void MaskOfFlySprite();

	static MaskSprites* create();

};

#endif 