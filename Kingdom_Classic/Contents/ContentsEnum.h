#pragma once

enum class ESpotUpgrade
{
	Tier0,
	Tier1,
	Tier2,
	Tier3,
	Tier4
};

enum class EObjectOrder
{
	Player,
	Monster,
	Back,
	Building
};

enum class ECollisionOrder
{
	Spot,
	Player,
	Monster
};

enum class ERenderOrder
{
	Sky,
	Back4,
	Back3,
	Back2,
	Back1,
	Back0,
	BackObject,
	Player,
	GroundObject,
	Ground,
	Water,
	UI
};