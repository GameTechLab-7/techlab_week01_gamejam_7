#pragma once

//#include "GameObject/Player.h"

class Player;

class BaseWeapon {
public:
	Player* currentPlayer;	// 그냥 플레이어 갖고 있을까 ㅇㅇ 그러자

	BaseWeapon(Player* player);

	virtual void Update(float tick) = 0;
};