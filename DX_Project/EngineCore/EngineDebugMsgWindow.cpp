#include "PreCompile.h"
#include "EngineDebugMsgWindow.h"

std::vector<std::string> UEngineDebugMsgWindow::Msg;

void UEngineDebugMsgWindow::PushMsg(std::string_view _Msg)
{
	Msg.push_back(_Msg.data());
}

UEngineDebugMsgWindow::UEngineDebugMsgWindow() 
{

}

UEngineDebugMsgWindow::~UEngineDebugMsgWindow() 
{

}

void UEngineDebugMsgWindow::Init()
{
	
}

void UEngineDebugMsgWindow::OnGui(float _Delta)
{
	for (size_t i = 0; i < Msg.size(); i++)
	{
		ImGui::Text(Msg[i].c_str());
	}

	Msg.clear();
}