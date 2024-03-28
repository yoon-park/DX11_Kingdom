#pragma once

#include <EnginePlatform/PreCompile.h>

#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineSound.h>
#include <EnginePlatform/EngineResources.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/WindowImage.h>

// FMOD
#include <EnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

// DirectX
#include <d3d11_4.h>		// DX 메인 헤더
#include <d3dcompiler.h>	// 쉐이더 컴파일러

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")