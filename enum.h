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
	UI,

	Max,
};

/** 방향 열거체 */
enum Direction : uint8_t
{
	Left ,
	Right ,
	Top ,
	Bottom ,
};

enum EScene :uint8_t {
	Title,
	Preset,
	MainGame,
	End,
};