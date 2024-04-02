#pragma once

class UCamera : public UTransformObject
{
public:
	UCamera();
	~UCamera();

	UCamera(const UCamera& _Other) = delete;
	UCamera(UCamera&& _Other) noexcept = delete;
	UCamera& operator=(const UCamera& _Other) = delete;
	UCamera& operator=(UCamera&& _Other) noexcept = delete;

protected:

private:

};