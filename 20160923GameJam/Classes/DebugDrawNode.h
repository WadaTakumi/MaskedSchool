#pragma once
#include "GLES-Render.h"

class DebugDrawNode:public cocos2d::Node
{
private:
	// 物理ワールド
	b2World*	m_pWorld;
	// デバッグ表示
	GLESDebugDraw* m_pDraw;
	// 描画コマンド
	cocos2d::CustomCommand m_Command;

public:
	DebugDrawNode();
	~DebugDrawNode();

	// インスタンス生成
	static DebugDrawNode* create(b2World* world);
	// 初期化
	bool init(b2World* world);
	// 描画
	void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags)override;

	void onDraw();
};

