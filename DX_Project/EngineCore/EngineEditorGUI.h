#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

class UEngineCore;
class UEngineEditorWindow;

class UEngineEditorGUI
{
	friend UEngineCore;
	friend UEngineEditorWindow;

public:
	UEngineEditorGUI();
	~UEngineEditorGUI();

	UEngineEditorGUI(const UEngineEditorGUI& _Other) = delete;
	UEngineEditorGUI(UEngineEditorGUI&& _Other) noexcept = delete;
	UEngineEditorGUI& operator=(const UEngineEditorGUI& _Other) = delete;
	UEngineEditorGUI& operator=(UEngineEditorGUI&& _Other) noexcept = delete;

	template<typename EditorWindowType>
	static std::shared_ptr<EditorWindowType> CreateEditorWindow(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		if (EditorWindows.contains(UpperName) == true)
		{
			MsgBoxAssert("같은 이름의 Window는 여러개 만들 수 없습니다.");
			return nullptr;
		}

		std::shared_ptr<UEngineEditorWindow> Windows = std::make_shared<EditorWindowType>();
		WindowInit(Windows, _Name);
		EditorWindows[UpperName] = Windows;
		return std::dynamic_pointer_cast<EditorWindowType>(Windows);
	}

	static void WindowOn(std::string_view _Name);
	static void WindowOff(std::string_view _Name);

protected:

private:
	static std::map<std::string, std::shared_ptr<UEngineEditorWindow>> EditorWindows;

	static void WindowInit(std::shared_ptr<UEngineEditorWindow> _Window, std::string_view _Name);
	static void GUIInit();
	static void GUIRender(float _DeltaTime);
	static void GUIRelease();
};