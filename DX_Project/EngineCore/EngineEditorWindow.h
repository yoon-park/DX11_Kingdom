#pragma once
#include "imgui.h"

class UEngineEditorGUI;

class UEngineEditorWindow : public UNameObject
{
	friend UEngineEditorGUI;

public:
	UEngineEditorWindow();
	~UEngineEditorWindow();

	UEngineEditorWindow(const UEngineEditorWindow& _Other) = delete;
	UEngineEditorWindow(UEngineEditorWindow&& _Other) noexcept = delete;
	UEngineEditorWindow& operator=(const UEngineEditorWindow& _Other) = delete;
	UEngineEditorWindow& operator=(UEngineEditorWindow&& _Other) noexcept = delete;

protected:
	virtual void Init() {}
	virtual void OnGui(float _Delta) = 0;

private:
	std::string Title;
	bool IsActive = true;

	void Begin();
	void End();
};