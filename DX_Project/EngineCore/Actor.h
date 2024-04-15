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

	FTransform& GetActorTransform();
	FVector GetActorScale3D();
	FVector GetActorLocation();
	FVector GetActorForwardVector();
	FVector GetActorRightVector();
	FVector GetActorUpVector();

	void SetActorTransform(const FTransform& _Transform);
	void SetActorScale3D(FVector _Value);
	void SetActorRotation(FVector _Value);
	void SetActorLocation(FVector _Value);

	void SetRoot(USceneComponent* _Root)
	{
		if (RootComponent != nullptr)
		{
			MsgBoxAssert("�̹� ��Ʈ�� �����߽��ϴ�.");
		}

		RootComponent = _Root;
	}

	void AddActorScale3D(FVector _Value);
	void AddActorRotation(FVector _Value);
	void AddActorLocation(FVector _Value);

	template<typename ComponentType>
	ComponentType* CreateDefaultSubObject(std::string_view _Name)
	{
		if (ULevel::IsActorConstructor == false)
		{
			MsgBoxAssert("������ �ۿ����� ������Ʈ�� �����Ҽ� �����ϴ�. (�𸮾��� ����)");
		}

		std::shared_ptr<UActorComponent> NewComponent = std::make_shared<ComponentType>();

		PushComponent(NewComponent, _Name);

		return dynamic_cast<ComponentType*>(NewComponent.get());
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USceneComponent* RootComponent = nullptr;
	std::vector<std::shared_ptr<UActorComponent>> Components;

	void PushComponent(std::shared_ptr<UActorComponent> _Component, std::string_view _Name);

// Input
public:
	static void OnlyInput(AActor* _this);
	static void OnlyInputStop();

	float GetPressTime(int _Key);

	void InputOn();
	void InputOff();

	bool IsAnykeyDown();
	bool IsAnykeyPress();
	bool IsAnykeyUp();
	bool IsAnykeyFree();

	bool IsDown(int _Key);
	bool IsPress(int _Key);
	bool IsUp(int _Key);
	bool IsFree(int _Key);
	bool IsDoubleClick(int _Key, float _ClickTime);

private:
	static std::set<AActor*> InputActors;
	static std::set<AActor*> PrevInputActors;
};