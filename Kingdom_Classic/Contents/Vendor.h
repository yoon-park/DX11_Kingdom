#pragma once
#include "BuildingObject.h"

#include "Tool.h"

class AVendor : public ABuildingObject
{
	GENERATED_BODY(ABuildingObject)

public:
	AVendor();
	~AVendor();

	AVendor(const AVendor& _Other) = delete;
	AVendor(AVendor&& _Other) noexcept = delete;
	AVendor& operator=(const AVendor& _Other) = delete;
	AVendor& operator=(AVendor&& _Other) noexcept = delete;

protected:
	USpriteRenderer* Renderer_NPC;
	USpriteRenderer* Renderer_Vendor;
	USpriteRenderer* Renderer_Sign;
	bool IsBuyable = true;
	int LeftSlot = 3;
	float Timer_Dir = 2.0f;

	std::vector<ATool*> Tools;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetDir(float _DeltaTime);
	void CheckIsBuyable();

	// State
	void StateInit();

	void InactiveStart();
	void ActiveStart();
	void BuyStart();

	void Inactive(float _DeltaTime);
	void Active(float _DeltaTime);
	void Buy(float _DeltaTime);

	void ActiveEnd();
	void BuyEnd();

private:

};