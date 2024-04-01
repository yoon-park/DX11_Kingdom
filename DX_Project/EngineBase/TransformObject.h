#pragma once
#include "Transform.h"

class UTransformObject
{
public:
	UTransformObject();
	~UTransformObject();

	UTransformObject(const UTransformObject& _Other) = delete;
	UTransformObject(UTransformObject&& _Other) noexcept = delete;
	UTransformObject& operator=(const UTransformObject& _Other) = delete;
	UTransformObject& operator=(UTransformObject&& _Other) noexcept = delete;

protected:

private:
	FTransform Transform;

	UTransformObject* Parent = nullptr;
	std::vector<UTransformObject*> Childs;
};