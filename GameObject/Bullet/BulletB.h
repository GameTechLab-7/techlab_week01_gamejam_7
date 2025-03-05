#pragma once

#include "GameObject/Bullet/Bullet.h"

// 무한 탄환
// 몬스터 통과
// 벽 무시
// 피격, 벽과 무관하게 존재한다. (ex - 회전 방어)

class BulletB : public Bullet {
	// Collision X

	virtual void HandleBallCollision(CircleObject& OtherBall) override;
};