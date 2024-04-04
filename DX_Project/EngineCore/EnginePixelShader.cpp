#include "PreCompile.h"
#include "EnginePixelShader.h"

#include "EngineCore.h"

UEnginePixelShader::UEnginePixelShader()
{
	Type = EShaderType::Pixel;
}

UEnginePixelShader::~UEnginePixelShader()
{
	if (ShaderPtr != nullptr)
	{
		ShaderPtr->Release();
	}
}

void UEnginePixelShader::ResLoad(std::string_view _EntryPoint, UINT _High, UINT _Low)
{
	EntryName = _EntryPoint;

	std::string Path = GetPath();
	const char* PathPtr = Path.c_str();
	std::wstring WPath = UEngineString::AnsiToUniCode(PathPtr);
	const wchar_t* WPathPtr = WPath.c_str();

	CONST D3D_SHADER_MACRO* pDefines = nullptr;
	
	ID3DInclude* pInclude = D3D_COMPILE_STANDARD_FILE_INCLUDE;
	
	const char* pEntrypoint = _EntryPoint.data();

	std::string Version = "ps_" + std::to_string(_High) + "_" + std::to_string(_Low);
	const char* Target = Version.c_str();

	int Flag0 = 0;
#ifdef _DEBUG
	Flag0 = D3D10_SHADER_DEBUG;
#endif
	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	int Flag1 = 0;

	HRESULT Result = D3DCompileFromFile(
		WPathPtr,
		pDefines,
		pInclude,
		pEntrypoint,
		Target,
		Flag0,
		Flag1,
		&ShaderCodeBlob,
		&ErrorCodeBlob
	);

	if (Result != S_OK)
	{
		std::string ErrorString = reinterpret_cast<char*>(ErrorCodeBlob->GetBufferPointer());
		MsgBoxAssert(ErrorString);
		return;
	}

	Result = GEngine->GetDirectXDevice()->CreatePixelShader(
		ShaderCodeBlob->GetBufferPointer(),
		ShaderCodeBlob->GetBufferSize(),
		nullptr,
		&ShaderPtr
	);

	if (Result != S_OK)
	{
		MsgBoxAssert("픽셀 쉐이더 생성에 실패했습니다.");
		return;
	}

	ShaderResCheck();
}

void UEnginePixelShader::Setting()
{
#ifdef _DEBUG
	if (ShaderPtr == nullptr)
	{
		MsgBoxAssert("만들어지지 않은 픽셀 쉐이더를 세팅하려 했습니다. : " + GetName());
	}
#endif

	GEngine->GetDirectXContext()->PSSetShader(ShaderPtr, nullptr, 0);
}