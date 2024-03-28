#pragma once

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
	static unsigned __int64 WindowMessageLoop(std::function<void()> _Update, std::function<void()> _End);

	HWND GetHWND() const
	{
		return hWnd;
	}
	std::shared_ptr<UWindowImage> GetWindowImage() const
	{
		return WindowImage;
	}
	std::shared_ptr<UWindowImage> GetBackBufferImage() const
	{
		return BackBufferImage;
	}
	FVector GetWindowScale() const
	{
		return Scale;
	}
	FVector GetMousePosition();

	void SetWindowPosition(const FVector& _Pos);
	void SetWindowScale(const FVector& _Scale);
	void SetWindowTitle(std::string_view _Text)
	{
		SetWindowTextA(hWnd, _Text.data());
	}
	void SetClearColor(Color8Bit _Color)
	{
		_Color.A = 0;
		ClearColor = _Color;
	}
	void SetWindowSmallIcon();
	void CursorOff();

	void Open(std::string_view _Title = "Title", std::string_view _IconPath = "");
	void ScreenClear();
	void ScreenUpdate();
	void Off()
	{
		WindowLive = false;
	}

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