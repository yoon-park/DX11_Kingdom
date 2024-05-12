#pragma once

enum class ENPCType
{
	Vagrant,
	Villager,
	Archer,
	Builder
};

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
	BowVendor,
	HammerVendor,
	None
};

enum class EObjectOrder
{
	Engine,
	Back,
	Building,
	Player,
	Monster,
	NPC,
	Other
};

enum class ECollisionOrder
{
	Horse,
	Player,
	Monster,
	NPC,
	OtherObject,
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
	BuildingBack,
	Building,
	BuildingFront,
	MovingActor,
	GroundObject,
	Ground,
	Water,
	UI
};