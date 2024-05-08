#pragma once

enum class EGroundType
{
	Plain,
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
	Engine,
	Back,
	Building,
	Player,
	Monster,
	Coin
};

enum class ECollisionOrder
{
	Coin,
	Spot,
	Horse,
	Player,
	Monster,
	NPC
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