#pragma once

class UContentsCore : public UserCore
{
public:
	UContentsCore();
	~UContentsCore();

	UContentsCore(const UContentsCore& _Other) = delete;
	UContentsCore(UContentsCore&& _Other) noexcept = delete;
	UContentsCore& operator=(const UContentsCore& _Other) = delete;
	UContentsCore& operator=(UContentsCore&& _Other) noexcept = delete;

protected:
	void Initialize() override;

private:

};