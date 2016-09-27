#pragma once
#include "GLES-Render.h"

class DebugDrawNode:public cocos2d::Node
{
private:
	// �������[���h
	b2World*	m_pWorld;
	// �f�o�b�O�\��
	GLESDebugDraw* m_pDraw;
	// �`��R�}���h
	cocos2d::CustomCommand m_Command;

public:
	DebugDrawNode();
	~DebugDrawNode();

	// �C���X�^���X����
	static DebugDrawNode* create(b2World* world);
	// ������
	bool init(b2World* world);
	// �`��
	void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags)override;

	void onDraw();
};

