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

	inline HWND GetHWND() const
	{
		return hWnd;
	}

	inline std::shared_ptr<UWindowImage> GetWindowImage() const
	{
		return WindowImage;
	}

	inline std::shared_ptr<UWindowImage> GetBackBufferImage() const
	{
		return BackBufferImage;
	}

	inline FVector GetWindowScale() const
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

	void Open(std::string_view _Title = "Title", std::string_view _IconPath = "");
	void ScreenClear();
	void ScreenUpdate();
	void CalculateMouseUpdate(float _DeltaTime);

	void Off()
	{
		WindowLive = false;
	}

	void CursorOff();

protected:

private:
	static HINSTANCE hInstance;
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static bool WindowLive;

	HWND hWnd = nullptr;
	FVector Position;
	FVector Scale;
	Color8Bit ClearColor = Color8Bit::WhiteA;

	std::shared_ptr<UWindowImage> WindowImage = nullptr;
	std::shared_ptr<UWindowImage> BackBufferImage = nullptr;

	float4 ScreenMousePrevPos;
	float4 ScreenMousePos;
	float4 ScreenMouseDir;
	float4 ScreenMouseDirNormal;

	FVector GetMousePosition();
};