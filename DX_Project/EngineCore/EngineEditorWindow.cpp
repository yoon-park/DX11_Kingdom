#include "PreCompile.h"
#include "EngineEditorWindow.h"

UEngineEditorWindow::UEngineEditorWindow()
{

}

UEngineEditorWindow::~UEngineEditorWindow()
{

}

void UEngineEditorWindow::Begin()
{
	std::string Name = GetName();

	ImGui::Begin(Name.c_str(), &IsActive);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
}

void UEngineEditorWindow::End()
{
	ImGui::End();
}