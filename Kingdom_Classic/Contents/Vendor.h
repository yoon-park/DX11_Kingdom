#pragma once

class AVendor : public AActor
{
	GENERATED_BODY(AActor)

public:
	AVendor();
	~AVendor();

	AVendor(const AVendor& _Other) = delete;
	AVendor(AVendor&& _Other) noexcept = delete;
	AVendor& operator=(const AVendor& _Other) = delete;
	AVendor& operator=(AVendor&& _Other) noexcept = delete;

	UStateManager State;

protected:
	UDefaultSceneComponent* Root;
	UCollision* Collision_Active;

private:

};