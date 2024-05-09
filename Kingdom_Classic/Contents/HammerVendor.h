#pragma once
#include "Vendor.h"

class AHammerVendor : public AVendor
{
	GENERATED_BODY(AVendor)

public:
	AHammerVendor();
	~AHammerVendor();

	AHammerVendor(const AHammerVendor& _Other) = delete;
	AHammerVendor(AHammerVendor&& _Other) noexcept = delete;
	AHammerVendor& operator=(const AHammerVendor& _Other) = delete;
	AHammerVendor& operator=(AHammerVendor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetCoinIndicatorLocation();

private:

};