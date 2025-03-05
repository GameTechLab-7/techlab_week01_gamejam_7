#pragma once

class Player;

class BaseWeapon
{
public:
	Player* currentPlayer;	// 그냥 플레이어 갖고 있을까 ㅇㅇ 그러자

	BaseWeapon(Player* player);
	virtual ~BaseWeapon() = default;

	virtual void Update(float DeltaTime) = 0;

	virtual void SetLevel(const int level) = 0;
};