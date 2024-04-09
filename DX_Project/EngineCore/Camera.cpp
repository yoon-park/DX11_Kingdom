#include "PreCompile.h"
#include "Camera.h"

#include "EngineCore.h"

UCamera::UCamera()
{
	InputOn();

	float4 Scale = GEngine->EngineWindow.GetWindowScale();
	ViewPort.Width = Scale.X;
	ViewPort.Height = Scale.Y;

	ViewPort.TopLeftX = 0;
	ViewPort.TopLeftY = 0;
	ViewPort.MinDepth = 0;
	ViewPort.MaxDepth = 1;
}

UCamera::~UCamera()
{

}

void UCamera::ViewPortSetting()
{
	GEngine->GetDirectXContext()->RSSetViewports(1, &ViewPort);
}

void UCamera::BeginPlay()
{

}

void UCamera::Tick(float _DeltaTime)
{
	int Key = GEngine->GetEngineOption().FreeCameraKey;

	if (IsFreeCamera == false && IsDown(Key))
	{
		PrevTransform = GetActorTransform();
		PrevProjectionType = ProjectionType;
		ProjectionType = ECameraType::Perspective;
		IsFreeCamera = true;
		OnlyInput(this);
	}
	else if (IsFreeCamera == true && IsDown(Key))
	{
		SetActorTransform(PrevTransform);
		ProjectionType = PrevProjectionType;
		IsFreeCamera = false;
		OnlyInputStop();

		return;
	}

	if (IsFreeCamera == false)
	{
		return;
	}

	if (IsDown('R') == true)
	{
		switch (ProjectionType)
		{
		case ECameraType::NONE:
			break;
		case ECameraType::Perspective:
			ProjectionType = ECameraType::Orthographic;
			break;
		case ECameraType::Orthographic:
			ProjectionType = ECameraType::Perspective;
			break;
		default:
			break;
		}
	}

	float Speed = FreeCameraMoveSpeed;

	if (IsPress(VK_LSHIFT) == true)
	{
		Speed = Speed * 4.0f;
	}

	if (IsPress('A') == true)
	{
		AddActorLocation(GetActorTransform().GetLeft() * _DeltaTime * Speed);
	}

	if (IsPress('D') == true)
	{
		AddActorLocation(GetActorTransform().GetRight() * _DeltaTime * Speed);
	}

	if (IsPress('Q') == true)
	{
		AddActorLocation(GetActorTransform().GetUp() * _DeltaTime * Speed);
	}

	if (IsPress('E') == true)
	{
		AddActorLocation(GetActorTransform().GetDown() * _DeltaTime * Speed);
	}

	if (IsPress('W') == true)
	{
		AddActorLocation(GetActorTransform().GetForward() * _DeltaTime * Speed);
	}

	if (IsPress('S') == true)
	{
		AddActorLocation(GetActorTransform().GetBack() * _DeltaTime * Speed);
	}

	if (IsPress(VK_RBUTTON) == true)
	{
		float4 Rot = GEngine->EngineWindow.GetScreenMouseDirNormal();

		AddActorRotation({ -Rot.Y, -Rot.X, 0.0f });
	}
}

void UCamera::CameraTransformUpdate()
{
	View.LookToLH(GetActorLocation(), GetActorForwardVector(), GetActorUpVector());

	FVector Scale = GEngine->EngineWindow.GetWindowScale();

	switch (ProjectionType)
	{
	case ECameraType::NONE:
		break;
	case ECameraType::Perspective:
		Projection.PerspectiveFovDeg(FOV, Scale.X, Scale.Y, Near, Far);
		break;
	case ECameraType::Orthographic:
		Projection.OrthographicLH(Scale.X, Scale.Y, Near, Far);
		break;
	default:
		break;
	}
}