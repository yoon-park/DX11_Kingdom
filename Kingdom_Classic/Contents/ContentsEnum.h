#pragma once

enum class EGroundType
{
	Plain,
	Plain_Grass,
	Forest,
	None
};

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
	Back,
	Building,
	Player,
	Monster,
	Coin
};

enum class ECollisionOrder
{
	Spot,
	Horse,
	Player,
	Monster,
	Coin
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
	Coin,
	Player,
	GroundObject,
	Ground,
	Water,
	UI
};