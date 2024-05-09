#pragma once
#include "BuildingObject.h"

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

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetDir();

	// State
	virtual void StateInit();

	virtual void InactiveStart();
	virtual void ActiveStart();
	virtual void BuyStart();

	virtual void Inactive(float _DeltaTime);
	virtual void Active(float _DeltaTime);
	virtual void Buy(float _DeltaTime);

	virtual void BuyEnd();

private:

};