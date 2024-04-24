#pragma once
#include "TickObject.h"
#include "WorldObject.h"
#include "Level.h"

class ULevel;
class UActorComponent;
class USceneComponent;

class AActor : public UTickObject, public UWorldObject, public UNameObject
{
	GENERATED_BODY(UTickObject)

	friend ULevel;

public:
	AActor();
	~AActor();

	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	template<typename ComponentType>
	ComponentType* CreateDefaultSubObject(std::string_view _Name)
	{
		if (ULevel::IsActorConstructer == false )
		{
			MsgBoxAssert("언리얼엔진에서는 액터의 생성자에서만 컴포넌트를 생성할 수 있습니다.");
		}
		
		std::shared_ptr<UActorComponent> NewComponent = std::make_shared<ComponentType>();
		PushComponent(NewComponent, _Name);
		return dynamic_cast<ComponentType*>(NewComponent.get());
	}

	FTransform& GetActorTransform();
	FVector GetActorScale3D();
	FVector GetActorLocation();
	FVector GetActorRightVector();
	FVector GetActorUpVector();
	FVector GetActorForwardVector();

	void SetActorTransform(const FTransform& _Transform);
	void SetActorScale3D(FVector _Value);
	void SetActorRotation(FVector _Value);
	void SetActorLocation(FVector _Value);

	void AddActorScale3D(FVector _Value);
	void AddActorRotation(FVector _Value);
	void AddActorLocation(FVector _Value);

	void SetRoot(USceneComponent* _Root)
	{
		if (RootComponent != nullptr)
		{
			MsgBoxAssert("이미 루트를 지정했습니다.");
		}

		RootComponent = _Root;
	}

	bool IsDestroy()
	{
		return IsDestroyValue;
	}

	void Destroy()
	{
		IsDestroyValue = true;
	}

	virtual void End() {};

	// Input
	static void OnlyInput(AActor* _this);
	static void OnlyInputStop();

	float GetPressTime(int _Key);

	void InputOn();
	void InputOff();

	bool IsDoubleClick(int _Key, float _ClickTime);
	bool IsDown(int _Key);
	bool IsPress(int _Key);
	bool IsUp(int _Key);
	bool IsFree(int _Key);
	bool IsAnykeyDown();
	bool IsAnykeyPress();
	bool IsAnykeyUp();
	bool IsAnykeyFree();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	static std::set<AActor*> InputActors;
	static std::set<AActor*> PrevInputActors;

	USceneComponent* RootComponent = nullptr;
	bool IsDestroyValue = false;

	std::vector<std::shared_ptr<UActorComponent>> Components;

	void PushComponent(std::shared_ptr<UActorComponent> _Component, std::string_view _Name);
};