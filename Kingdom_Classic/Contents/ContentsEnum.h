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

enum class EBuildingObjectType
{
	Spot,
	Vendor,
	None
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
	Horse,
	Player,
	Monster,
	NPC,
	Coin,
	BuildingObject
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
	Building,
	Player,
	GroundObject,
	Ground,
	Water,
	UI
};