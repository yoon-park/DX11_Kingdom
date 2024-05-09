#pragma once
#include "Vendor.h"

class ABowVendor : public AVendor
{
	GENERATED_BODY(AVendor)

public:
	ABowVendor();
	~ABowVendor();

	ABowVendor(const ABowVendor& _Other) = delete;
	ABowVendor(ABowVendor&& _Other) noexcept = delete;
	ABowVendor& operator=(const ABowVendor& _Other) = delete;
	ABowVendor& operator=(ABowVendor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetCoinIndicatorLocation();

private:

};