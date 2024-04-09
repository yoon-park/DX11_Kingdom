#pragma once
#include "EngineEnums.h"
#include "Actor.h"

class ULevel;

class UCamera : public AActor
{
	friend ULevel;
	friend URenderer;

public:
	UCamera();
	~UCamera();

	UCamera(const UCamera& _Other) = delete;
	UCamera(UCamera&& _Other) noexcept = delete;
	UCamera& operator=(const UCamera& _Other) = delete;
	UCamera& operator=(UCamera&& _Other) noexcept = delete;

	inline FMatrix GetView()
	{
		return View;
	}

	inline FMatrix GetProjection()
	{
		return Projection;
	}

	inline void SetNear(float _Value)
	{
		Near = _Value;
	}

	inline void SetFar(float _Value)
	{
		Far = _Value;
	}

	void ViewPortSetting();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	bool IsFreeCamera = false;

	ECameraType ProjectionType = ECameraType::Orthographic;
	float Near = 1.0f;
	float Far = 10000.0f;
	float FOV = 60.0f;

	FMatrix View;
	FMatrix Projection;
	D3D11_VIEWPORT ViewPort;

	void CameraTransformUpdate();
};