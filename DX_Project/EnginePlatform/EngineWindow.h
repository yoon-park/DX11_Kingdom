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
	static void SetUserWindowCallBack(std::function<bool(HWND, UINT, WPARAM, LPARAM)> _UserWndProcFunction);

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

	inline float4 GetScreenMousePrevPos()
	{
		return ScreenMousePrevPos;
	}

	inline float4 GetScreenMousePos()
	{
		return ScreenMousePos;
	}

	inline float4 GetScreenMouseDir()
	{
		return ScreenMouseDir;
	}

	inline float4 GetScreenMouseDirNormal()
	{
		return ScreenMouseDirNormal;
	}

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
	void ScreenClear();
	void ScreenUpdate();

	void Off()
	{
		WindowLive = false;
	}

	void CalculateMouseUpdate(float _DeltaTime);
	void CursorOff();

protected:

private:
	static bool WindowLive;
	static HINSTANCE hInstance;
	static std::function<bool(HWND, UINT, WPARAM, LPARAM)> UserWndProcFunction;

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	HWND hWnd = nullptr;
	std::shared_ptr<UWindowImage> WindowImage = nullptr;
	std::shared_ptr<UWindowImage> BackBufferImage = nullptr;
	FVector Scale;
	FVector Position;
	Color8Bit ClearColor = Color8Bit::WhiteA;
	float4 ScreenMousePrevPos;
	float4 ScreenMousePos;
	float4 ScreenMouseDir;
	float4 ScreenMouseDirNormal;

	FVector GetMousePosition();
};