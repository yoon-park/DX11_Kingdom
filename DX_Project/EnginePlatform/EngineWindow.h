#pragma once
#include <Windows.h>
#include <string>
#include <memory>

#include <EngineBase\EngineMath.h>

class UWindowImage;

class UEngineWindow
{
public:
	UEngineWindow();
	~UEngineWindow();

	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	static void Init(HINSTANCE _hInst);
	static unsigned __int64 WindowMessageLoop(void(*_Update)(), void(*_End)());

	std::shared_ptr<UWindowImage> GetWindowImage()
	{
		return WindowImage;
	}

	std::shared_ptr<UWindowImage> GetBackBufferImage()
	{
		return BackBufferImage;
	}

	FVector GetWindowScale()
	{
		return Scale;
	}

	FVector GetMousePosition();

	void SetWindowPosition(const FVector& _Pos);
	void SetWindowScale(const FVector& _Scale);

	void SetClearColor(Color8Bit _Color)
	{
		_Color.A = 0;
		ClearColor = _Color;
	}

	void SetWindowTitle(std::string_view _Text)
	{
		SetWindowTextA(hWnd, _Text.data());
	}

	void SetWindowSmallIcon();

	void Open(std::string_view _Title = "Title", std::string_view _IconPath = "");

	void Off()
	{
		WindowLive = false;
	}

	void ScreenClear();
	void ScreenUpdate();

	void CursorOff();

protected:

private:
	static bool WindowLive;
	static HINSTANCE hInstance;
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	HWND hWnd = nullptr;
	FVector Position;
	FVector Scale;
	Color8Bit ClearColor = Color8Bit::WhiteA;

	std::shared_ptr<UWindowImage> WindowImage = nullptr;
	std::shared_ptr<UWindowImage> BackBufferImage = nullptr;
};