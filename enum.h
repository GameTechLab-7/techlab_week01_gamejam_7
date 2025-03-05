#pragma once
#include <cstdint>


enum EWorld : uint8_t
{
	First,
	Second,
};


enum class EObjectType : uint8_t
{
    Player = 0,
    Enemy,
    Bullet,

    Max,
};
