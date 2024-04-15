#include "PreCompile.h"
#include "Actor.h"

#include "SceneComponent.h"
#include "DefaultSceneComponent.h"

std::set<AActor*> AActor::InputActors;
std::set<AActor*> AActor::PrevInputActors;

AActor::AActor()
{

}

AActor::~AActor()
{

}

FTransform& AActor::GetActorTransform()
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	return RootComponent->Transform;
}

FVector AActor::GetActorScale3D()
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	return RootComponent->GetWorldScale();
}

FVector AActor::GetActorLocation()
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	return RootComponent->GetWorldPosition();
}

FVector AActor::GetActorRightVector()
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	return RootComponent->GetWorldRight();
}

FVector AActor::GetActorUpVector()
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	return RootComponent->GetWorldRight();
}

FVector AActor::GetActorForwardVector()
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	return RootComponent->GetWorldForward();
}

void AActor::SetActorTransform(const FTransform& _Transform)
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	RootComponent->Transform = _Transform;
}

void AActor::SetActorScale3D(FVector _Value)
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	RootComponent->SetScale(_Value);
}

void AActor::SetActorRotation(FVector _Value)
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	RootComponent->SetRotationDeg(_Value);
}

void AActor::SetActorLocation(FVector _Value)
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	RootComponent->SetPosition(_Value);
}

void AActor::AddActorScale3D(FVector _Value)
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	RootComponent->AddScale(_Value);
}

void AActor::AddActorRotation(FVector _Value)
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	RootComponent->AddRotationDeg(_Value);
}

void AActor::AddActorLocation(FVector _Value)
{
#ifdef _DEBUG
	if (RootComponent == nullptr)
	{
		MsgBoxAssert("루트컴포넌트가 지정되지 않았습니다.");
	}
#endif

	RootComponent->AddPosition(_Value);
}

void AActor::BeginPlay()
{
	Super::BeginPlay();

	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->SetWorld(GetWorld());
		Components[i]->BeginPlay();
	}
}

void AActor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	for (size_t i = 0; i < Components.size(); i++)
	{
		if (Components[i]->IsActive() == false)
		{
			continue;
		}

		Components[i]->Tick(_DeltaTime);
	}
}

void AActor::PushComponent(std::shared_ptr<UActorComponent> _Component, std::string_view _Name)
{
	_Component->SetActor(this);
	_Component->SetName(_Name);
	Components.push_back(_Component);

	std::shared_ptr<USceneComponent> SceneComponent = std::dynamic_pointer_cast<USceneComponent>(_Component);
}

void AActor::OnlyInput(AActor* _this)
{
	PrevInputActors = InputActors;
	InputActors.clear();
	InputActors.insert(_this);
}

void AActor::OnlyInputStop()
{
	InputActors.clear();
	InputActors = PrevInputActors;
}

float AActor::GetPressTime(int _Key)
{
	if (InputActors.contains(this) == false)
	{
		return false;
	}

	return UEngineInput::GetPressTime(_Key);
}

void AActor::InputOn()
{
	InputActors.insert(this);
}

void AActor::InputOff()
{
	InputActors.erase(this);
}

bool AActor::IsAnykeyDown()
{
	if (InputActors.contains(this) == false)
	{
		return false;
	}

	return UEngineInput::IsAnykeyDown();
}

bool AActor::IsAnykeyPress() 
{
	if (InputActors.contains(this) == false)
	{
		return false;
	}

	return UEngineInput::IsAnykeyPress();
}

bool AActor::IsAnykeyUp()
{
	if (InputActors.contains(this) == false)
	{
		return false;
	}

	return UEngineInput::IsAnykeyUp();
}

bool AActor::IsAnykeyFree()
{
	if (InputActors.contains(this) == false)
	{
		return false;
	}

	return UEngineInput::IsAnykeyFree();
}

bool AActor::IsDown(int _Key)
{
	if (InputActors.contains(this) == false)
	{
		return false;
	}

	return UEngineInput::IsDown(_Key);
}

bool AActor::IsPress(int _Key)
{
	if (InputActors.contains(this) == false)
	{
		return false;
	}

	return UEngineInput::IsPress(_Key);
}


bool AActor::IsUp(int _Key)
{
	if (InputActors.contains(this) == false)
	{
		return false;
	}

	return UEngineInput::IsUp(_Key);
}

bool AActor::IsFree(int _Key) 
{
	if (InputActors.contains(this) == false)
	{
		return false;
	}

	return UEngineInput::IsFree(_Key);
}

bool AActor::IsDoubleClick(int _Key, float _ClickTime)
{
	if (InputActors.contains(this) == false)
	{
		return false;
	}

	return UEngineInput::IsDoubleClick(_Key, _ClickTime);
}