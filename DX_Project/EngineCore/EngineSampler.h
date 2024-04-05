#pragma once

class UEngineSampler
{
public:
	UEngineSampler();
	~UEngineSampler();

	UEngineSampler(const UEngineSampler& _Other) = delete;
	UEngineSampler(UEngineSampler&& _Other) noexcept = delete;
	UEngineSampler& operator=(const UEngineSampler& _Other) = delete;
	UEngineSampler& operator=(UEngineSampler&& _Other) noexcept = delete;

protected:

private:

};